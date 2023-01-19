﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VkNet;
using VkNet.Enums.Filters;
using VkNet.Enums.SafetyEnums;
using VkNet.Model;
using VkNet.Model.RequestParams;
using VkNet.Utils;
using MySql.Data.MySqlClient;
using VkNet.Model.Keyboard;

namespace Mines
{
    internal class Program
    {
        static MySqlConnection connection;

        static MySqlCommand command;

        static System.Collections.ObjectModel.Collection<Message> messages;

        static readonly VkApi api = new VkApi();

        static Random rnd = new Random();

        static List<Mine> GetMines(long id)
        {
            command.CommandText = $"SELECT * FROM `mines` WHERE `owner_id`={id}";
            MySqlDataReader reader = command.ExecuteReader();

            List<Mine> mines = new List<Mine>();
            if (reader.HasRows)
            {
                while (reader.Read())
                {
                    mines.Add(new Mine()
                    {
                        Id = reader.GetInt16("id"),
                        OwnerId = reader.GetInt64("owner_id"),
                        Deep = reader.GetInt32("deep"),
                        Income = reader.GetDouble("income")
                    });
                }
                reader.Close();

                return mines;
            }
            else
            {
                reader.Close();
                return null;
            }
        }
        static void Message(string message, long? id, bool keys, List<int> prm, int menu)
        {
            KeyboardBuilder keyboard = new KeyboardBuilder();

            if (keys)
            {
                if (menu == 0)
                {
                    keyboard.AddButton(new AddButtonParams { Label = "Статистика", Color = KeyboardButtonColor.Default });
                    keyboard.AddButton(new AddButtonParams { Label = "Шахты", Color = KeyboardButtonColor.Default });
                }
                if (menu / 100 == 1)
                {
                    for (int i = 0; i < prm.Count; i++)
                    {
                        if ((i + 1) % 3 == 0)
                            keyboard.AddLine();
                        keyboard.AddButton(new AddButtonParams { Label = $"Улучшить шахту {prm[i]}", Color = KeyboardButtonColor.Primary });
                    }
                    keyboard.AddLine();

                    bool flag = false;
                    if (menu % 100 < prm.Count / 10 + 1)
                    {
                        flag = true;
                        keyboard.AddButton(new AddButtonParams { Label = "Следующая", Color = KeyboardButtonColor.Positive });
                    }
                    if (menu % 100 > 1)
                    {
                        if (flag)
                            keyboard.AddLine();
                        keyboard.AddButton(new AddButtonParams { Label = "Предыдущая", Color = KeyboardButtonColor.Positive });
                    }
                }
            }

            try
            {
                api.Messages.Send(new MessagesSendParams
                {
                    RandomId = rnd.Next(0, 1000000000),
                    PeerId = id,
                    Message = message,
                    Keyboard = keyboard.Build()
                });
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        static void SetMenu(long? id, int menu)
        {
            command.CommandText = $"UPDATE `players` SET `menu`={menu} WHERE `id` = {id}";
            command.ExecuteNonQuery();
        }

        static Player GetPlayer(long id)
        {
            Player player;
            command.CommandText = $"SELECT * FROM `players` WHERE `id`={id}";
            MySqlDataReader reader = command.ExecuteReader();
            if (reader.HasRows)
            {
                reader.Read();
                player = new Player
                {
                    Id = reader.GetInt64("id"),
                    MinesCount = reader.GetInt16("minescount"),
                    Gold = reader.GetDouble("gold"),
                    Menu = reader.GetInt32("menu")
                };
                reader.Close();
            }
            else
            {
                reader.Close();
                command.CommandText = $"INSERT INTO `players`(`id`,`minescount`,`gold`,`menu`) VALUES({id},0,0,0)";
                command.ExecuteNonQuery();
                player = new Player
                {
                    Id = id,
                    MinesCount = 0,
                    Gold = 0,
                    Menu = 0
                };
            }
            return player;
        }
        static void Main(string[] args)
        {
            api.Authorize(new ApiAuthParams
            {
                AccessToken = "vk1.a.Wg6_z2HqNJHRC2qVGmNvxYONAjkSbHL5PnwjiP5DKDVjelgF_h4-RFL23ny9egL9rKxCipRqOrsPJiywhJhE5dDzZ8FdbMhMQ53A76qyY5OW0JnTCuDeVJzTnoZPd7X5z4q4AytJQQzP_cGTTLn89IZ63k3eZd2971CAsLkJdGUsba37uciGfCD7vMbjpNVPHikKMOJmVmqQ-SZUMtrTmA"
            });

            string connectionParameters = "Server=localhost;Database=mines;Port=3306;User=root;Password=;SslMode=none";
            connection = new MySqlConnection(connectionParameters);
            connection.Open();
            command = new MySqlCommand() { Connection = connection };

            DateTime lastIncome = DateTime.Now;
            while (true)
            {
                if (lastIncome.Minute != DateTime.Now.Minute)
                {
                    command.CommandText = "UPDATE `players` SET `gold`=`gold`+(SELECT SUM(`income`)+0 FROM `mines` WHERE `owner_id` = `players`.`id`)";
                    command.ExecuteNonQuery();
                    lastIncome = DateTime.Now;
                }

                GetConversationsResult result = api.Messages.GetConversations(new GetConversationsParams { Filter = GetConversationFilter.Unanswered });

                for (int u = 0; u < result.Count; u++)
                {
                    MessageGetHistoryObject history = api.Messages.GetHistory(new MessagesGetHistoryParams
                    {
                        UserId = result.Items[u].Conversation.Peer.Id,
                        Count = 1
                    });

                    Player player = GetPlayer(result.Items[u].Conversation.Peer.Id);
                    messages = history.Messages.ToCollection();

                    switch (messages[0].Text.ToLower())
                    {
                        case "начать":
                            {
                                Message("🖥Список команд:\n📊Статистика - Вывод статистики\n⏲Шахты - Вывод списка шахт", player.Id, true, null, player.Menu);
                                break;
                            }
                        case "меню":
                            {
                                goto case "начать";
                            }
                        case "статистика":
                            {
                                Message($"📊Статистика:\n⏲Количество Шахт: {player.MinesCount}\n💰Золото: {player.Gold}", player.Id, true, null, player.Menu);
                                break;
                            }
                        case "шахты":
                            {
                                Console.WriteLine(player.Menu);
                                string answer = "⏲Ваши шахты:\n";
                                List<Mine> mines = GetMines(player.Id);
                                List<int> minesIds = new List<int>();

                                if (mines != null)
                                {
                                    if (player.Menu / 100 != 1 || player.Menu == 100 || player.Menu % 100 > mines.Count / 10 + 1)
                                    {
                                        player.Menu = 101;
                                        SetMenu(player.Id, player.Menu);
                                    }

                                    for (int i = 10 * (player.Menu % 100) - 10; i < Math.Min(player.Menu % 100 * 10, mines.Count); i++)
                                    {
                                        minesIds.Add(mines[i].Id);
                                        answer += $"♨Шахта №{mines[i].Id} 💰{mines[i].Income}/мин 🕳{mines[i].Deep}\n";
                                    }
                                    Message(answer, player.Id, true, minesIds, player.Menu);
                                }
                                else
                                {
                                    player.Menu = 100;
                                    SetMenu(player.Id, player.Menu);

                                    Message("🚫У вас нет шахт", player.Id, true, null, player.Menu);
                                }
                                break;
                            }
                        case "следующая":
                            {
                                if (player.Menu / 100 == 1)
                                {
                                    player.Menu++;
                                    SetMenu(player.Id, player.Menu);
                                    goto case "шахты";
                                }
                                break;
                            }
                        case "предыдущая":
                            {
                                if (player.Menu / 100 == 1)
                                {
                                    player.Menu--;
                                    SetMenu(player.Id, player.Menu);
                                    goto case "шахты";
                                }
                                break;
                            }
                        default:
                            {
                                SetMenu(player.Id, 0);
                                Message("SERVER SENT CODE 404", player.Id, false, null, 0);
                                break;
                            }
                    }
                }
            }

        }
    }
}
