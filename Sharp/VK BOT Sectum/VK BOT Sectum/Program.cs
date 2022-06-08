using System;
using System.Collections.Generic;
using VkNet;
using VkNet.Enums.SafetyEnums;
using VkNet.Model;
using VkNet.Model.RequestParams;
using System.IO;
using System.Diagnostics;

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

        static bool CheckId(VkNet.Utils.VkCollection<User> us, long? id)
        {
            for (int i = 0; i < us.Count; i++)
            {
                if (id == us[i].Id)
                    return true;
            }
            return false;
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
                    var us = api.Groups.GetMembers(new GroupsGetMembersParams() { GroupId = "210381180" });
                    var conv = api.Messages.GetConversations(new GetConversationsParams() { Filter = GetConversationFilter.Unread }).Items;

                    int count = conv.Count;
                    for (int i = 0; i < count; i++)
                    {
                        long? id = conv[i].LastMessage.FromId;
                        if (CheckId(us, id))
                        {
                            try
                            {
                                StreamReader reader = new StreamReader(conv[i].LastMessage.Text + ".txt");
                                string Answer = reader.ReadToEnd();
                                do
                                {
                                    SendMessage(id, Answer.Substring(0, Math.Min(Answer.Length, 4096)));
                                    if (Answer.Length > 4096)
                                        Answer = Answer.Substring(4096, Answer.Length - 4096);
                                }
                                while (Answer.Length > 4096);
                                reader.Close();
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
                }
            }
            catch (Exception e)
            {
                Process.Start("VK BOT INSPECTOR.exe", rnd.Next(0, 100).ToString());
            }
        }
    }
}
