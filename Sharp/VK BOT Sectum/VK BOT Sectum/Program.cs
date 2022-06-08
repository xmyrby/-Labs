using System;
using VkNet;
using VkNet.Enums.SafetyEnums;
using VkNet.Model;
using VkNet.Model.RequestParams;
using System.IO;
using System.Diagnostics;
using VkNet.Enums.Filters;
using System.Linq;
using System.Threading;

namespace VK_BOT_Sectum
{
    class Program
    {
        static Random rnd = new Random();
        static readonly VkApi api = new VkApi();
        static void SendMessage(long? id, string message)
        {
            try
            {
                api.Messages.Send(new MessagesSendParams
                {
                    RandomId = rnd.Next(0, 1000000000),
                    PeerId = id,
                    Message = message
                });
            }
            catch
            {

            }

        }
        static string GetVkName(long? id)
        {
            try
            {
                var user = api.Users.Get(new long[] { (long)(id) }, ProfileFields.FirstName | ProfileFields.LastName);

                return user[0].FirstName + " " + user[0].LastName;
            }
            catch
            {
                return "[GetVkName ERROR, Input id probably 0]";
            }
        }
        static void Main()
        {
            api.Authorize(new ApiAuthParams
            {
                AccessToken = "5a984a41bfd2641df44c300669f368878c74cf99ef01803ca7227a2dc7098d627fc75682f9f48a5d9068f"
            });
            try
            {
                while (true)
                {
                    var conv = api.Messages.GetConversations(new GetConversationsParams() { Filter = GetConversationFilter.Unread }).Items;

                    int count = conv.Count;
                    for (int i = 0; i < count; i++)
                    {
                        long? id = conv[i].LastMessage.FromId;
                        if (api.Groups.IsMember("210381180", id, null, null).Select(x => x.Member).FirstOrDefault())
                        {
                            try
                            {
                                StreamReader reader = new StreamReader(conv[i].LastMessage.Text + ".txt");
                                string Answer = reader.ReadToEnd();
                                if (Answer.Length > 4096)
                                {
                                    int c = Answer.Length / 4096 + 1;
                                    for (int j = 0; j < c; j++)
                                    {
                                        SendMessage(id, Answer.Substring(0, Math.Min(Answer.Length, 4096)));
                                        if (Answer.Length > 4096)
                                            Answer = Answer.Substring(4096, Answer.Length - 4096);
                                    }
                                }
                                else
                                {
                                    SendMessage(id, Answer);
                                }
                                reader.Close();

                                StreamWriter writer = new StreamWriter("Logs.txt", true);
                                writer.WriteLine(DateTime.Now + " " + GetVkName(id) + " asked question #" + conv[i].LastMessage.Text);
                                writer.Close();
                            }
                            catch (Exception e)
                            {
                                SendMessage(id, "Долбоёб?\nВведи нормально номер билета еблан");
                            }
                        }
                        else
                        {
                            SendMessage(id, "Подпишись");
                        }
                    }
                    Thread.Sleep(1000);
                }
            }
            catch (Exception e)
            {
                StreamWriter writer = new StreamWriter("Logs.txt", true);
                writer.WriteLine(e.ToString());
                writer.Close();
                Process.Start("VK BOT Sectum.exe", rnd.Next(0, 100).ToString());
            }
        }
    }
}
