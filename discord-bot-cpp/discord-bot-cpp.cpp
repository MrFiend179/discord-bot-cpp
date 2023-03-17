#include <dpp/dpp.h>
#include <cstdlib>
#include <ctime>
#include <dpp/cluster.h>

int main() {
	std::string token_by_usr;
	for (int i = 0; i < 5; i++) {
		std::cout << "Enter The Discord Bots Token: ";
		std::cin >> token_by_usr;
		if (token_by_usr.length() <= 63) {
			std::cout << "Enter a valid token!\n";
		}
		else {
			const std::string BOT_TOKEN = token_by_usr;

			dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content | dpp::r_mentionable);
			std::srand(std::time(nullptr));
			bot.on_log(dpp::utility::cout_logger());
			bot.on_slashcommand([](const dpp::slashcommand_t& event) {
				if (event.command.get_command_name() == "gamble") {
					std::string rndgmbl[] = {
							"Straight flush",
							"Four of a kind",
							"Full House",
							"Flush",
							"Straight",
							"Three of a kind",
							"One pair",
							"Two pair"
					};
					const int rndgmbll = sizeof(rndgmbl) / sizeof(std::string);
					int random_gambel = std::rand() % rndgmbll;
					event.reply(rndgmbl[random_gambel]);
				}
				});
			bot.on_ready([&bot](const dpp::ready_t& event) {
				std::cout << "Bot " << bot.me.username << "#" << bot.me.discriminator << " is ready!\n";
				if (dpp::run_once<struct register_bot_commands>()) {
					bot.global_command_create(dpp::slashcommand("gamble", "A Gamble!", bot.me.id));
				}
			});
			bot.on_message_create([&bot](const dpp::message_create_t& event) {
				if (event.msg.content.starts_with("-kill")) {
					if (event.msg.mentions.size() > 0) {
						dpp::snowflake user_mention = event.msg.mentions[0].first.id;
						std::string user_mentions = "<@" + std::to_string(user_mention) + ">";
						std::string randomwpn[] = {
							"rock",
							"stick",
							"stone",
							"coconut",
							"watermelon",
							"spoon",
							"picture of JFK",
							"piece of hair"
						};
						const int kll_wpn = sizeof(randomwpn) / sizeof(std::string);
						int tkll_wpm = std::rand() % kll_wpn;
						std::string randomklr[] = {
							"cat",
							"dog",
							"capybara",
							"octopus",
							"shadow",
							"goose",
							"parrot"
							"panda"
						};
						const int kll_klr = sizeof(randomklr) / sizeof(std::string);
						int tkll_klr = std::rand() % kll_klr;
						bot.message_create(dpp::message(event.msg.channel_id, "A " + randomklr[tkll_klr] + " killed " + user_mentions + " with a " + randomwpn[tkll_wpm]));
					}
					else {
						bot.message_create(dpp::message(event.msg.channel_id, "You forgot to mention someone!"));
					};
				}
				if (event.msg.content.starts_with("-pm")) {
					if (event.msg.mentions.size() > 0) {
						dpp::snowflake user_to_dm = event.msg.mentions[0].first.id;
						dpp::message msg_dm;
						std::string message_to_send = event.msg.content.substr(25);
						msg_dm.content = message_to_send;
						bot.direct_message_create(user_to_dm, msg_dm);
					}
					else {
						bot.message_create(dpp::message(event.msg.channel_id, "You forgot to mention someone!"));
					}
				}
				if (event.msg.content.starts_with("-iq")) {
					int rand_iq = (rand() % 71) + 60;
					if (event.msg.mentions.size() > 0) {
						dpp::snowflake usr_to_add = event.msg.mentions[0].first.id;
						std::string sctm_str_usr = "<@" + std::to_string(usr_to_add) + ">";
						bot.message_create(dpp::message(event.msg.channel_id, sctm_str_usr + " has an iq of " + std::to_string(rand_iq)));
					}
					else {
						bot.message_create(dpp::message(event.msg.channel_id, "This shows you have 0 iq, enter a user"));
					}
				}
				
				if (event.msg.content.find("-mck") == 0) {
					std::string command = event.msg.content.substr(4);
					std::string randvoid[] = {
						"*a space*",
						"*void*",
						"*silence*",
						"*nothing to mock*"
					};
					const int num_sentences = sizeof(randvoid) / sizeof(std::string);
					std::srand(std::time(nullptr));
					int index = std::rand() % num_sentences;
					if (command != "") {
						bot.message_create(dpp::message(event.msg.channel_id, command));
					}
					else {
						bot.message_create(dpp::message(event.msg.channel_id, randvoid[index]));
					}
				}
				if (event.msg.content.find("-mock") == 0) {
					std::string command = event.msg.content.substr(5);
					std::string randvoid[] = {
						"*a space*",
						"*void*",
						"*silence*",
						"*nothing to mock*"
					};
					const int num_sentences = sizeof(randvoid) / sizeof(std::string);
					std::srand(std::time(nullptr));
					int index = std::rand() % num_sentences;
					if (command != "") {
						bot.message_create(dpp::message(event.msg.channel_id, command));
					}
					else {
						bot.message_create(dpp::message(event.msg.channel_id, randvoid[index]));
					}
				}
				if (event.msg.content.starts_with("-av") || event.msg.content.starts_with("-Av") || event.msg.content.starts_with("-avatar") || event.msg.content.starts_with("-Avatar")) {
					if (event.msg.mentions.size() > 0) {
						std::string useravturl = event.msg.mentions[0].first.get_avatar_url();
						dpp::embed embed;
						embed.set_author(event.msg.mentions[0].first.format_username(), "", useravturl);
						embed.set_image(useravturl + "?size=4096");
						embed.set_title("User Avatar");
						bot.message_create(dpp::message(event.msg.channel_id, embed));
					}
					else {
						dpp::embed embed;
						embed.set_author(event.msg.author.format_username(), "", event.msg.author.get_avatar_url());
						embed.set_image(event.msg.author.get_avatar_url() + "?size=4096");
						embed.set_title("User Avatar");
						bot.message_create(dpp::message(event.msg.channel_id, embed));
					}
				}
				if (event.msg.content == "-info" || event.msg.content == "-help") {
					const uint32_t colors[] = {
							dpp::colors::aquamarine,
							dpp::colors::blue,
							dpp::colors::cyan,
							dpp::colors::scarlet_red,
							dpp::colors::forest_green,
							dpp::colors::raspberry,
							dpp::colors::rallyart_crimson,
							dpp::colors::moon_yellow
					};
					const int clr = sizeof(colors) / sizeof(const uint32_t);
					int rnd_colors = std::rand() % clr;
					dpp::embed embed = dpp::embed().
						set_color(colors[rnd_colors]).
						set_title("Commands").
						set_author("Centaur", "", bot.me.get_avatar_url()).
						set_description("Use the Following Command to interact with the bot").
						add_field(
							"-kill",
							"Kills the mentioned user virtually"
						).
						add_field(
							"-avatar",
							"Shows the mentioned users avatar"
						).
						set_footer(dpp::embed_footer().set_text("Made in C++").set_icon("")).
						add_field(
							"-iq",
							"Shows the iq level"
						).
						add_field(
							"-mck",
							"Mimicks what you say in the chat"
						).
						add_field(
							"-pm",
							"Sends a message to the mentioned user in DM's"
						).

						set_timestamp(time(0));

					bot.message_create(dpp::message(event.msg.channel_id, embed).set_reference(event.msg.id));
				}

				});
			bot.start(false);
			break;
			return 0;
		}
	}
}
