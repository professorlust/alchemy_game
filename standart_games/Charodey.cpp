#include "../Game.hpp"

void Game::charodey(std::vector <sf::Texture> &item_textures_copy, std::vector<Item> &items_list_copy, std::vector<Reaction> &reactions_list_copy, std::vector<Reagent> &started_items_copy)
{
	name = "Charodey";
	author = "default";
	description = "Standard test game. FOR THIS TIME IS NOT FINISHED\nYa inglish-man &blacksun&";

	int number_of_textures = 60;
	for (int i = 0; i < number_of_textures; ++i)
		item_textures_copy.push_back(sf::Texture());

	item_textures_copy[0].loadFromFile("standart_games_sp/charodey/fire.png");
	item_textures_copy[1].loadFromFile("standart_games_sp/charodey/water.png");
	item_textures_copy[2].loadFromFile("standart_games_sp/charodey/earth.png");
	item_textures_copy[3].loadFromFile("standart_games_sp/charodey/air.png");
	item_textures_copy[4].loadFromFile("standart_games_sp/charodey/lava.png");
	item_textures_copy[5].loadFromFile("standart_games_sp/charodey/swamp.png");
	item_textures_copy[6].loadFromFile("standart_games_sp/charodey/alcohol.png");
	item_textures_copy[7].loadFromFile("standart_games_sp/charodey/stone.png");
	item_textures_copy[8].loadFromFile("standart_games_sp/charodey/sand.png");
	item_textures_copy[9].loadFromFile("standart_games_sp/charodey/steam.png");
	item_textures_copy[10].loadFromFile("standart_games_sp/charodey/energy.png");
	item_textures_copy[11].loadFromFile("standart_games_sp/charodey/glass.png");
	item_textures_copy[12].loadFromFile("standart_games_sp/charodey/spark.png");
	item_textures_copy[13].loadFromFile("standart_games_sp/charodey/clay.png");
	item_textures_copy[14].loadFromFile("standart_games_sp/charodey/brick.png");
	item_textures_copy[15].loadFromFile("standart_games_sp/charodey/dust.png");
	item_textures_copy[16].loadFromFile("standart_games_sp/charodey/desert.png");
	item_textures_copy[17].loadFromFile("standart_games_sp/charodey/philosophers_stone.png");
	item_textures_copy[18].loadFromFile("standart_games_sp/charodey/life.png");
	item_textures_copy[19].loadFromFile("standart_games_sp/charodey/bacteria.png");
	item_textures_copy[20].loadFromFile("standart_games_sp/charodey/seaweed.png");
	item_textures_copy[21].loadFromFile("standart_games_sp/charodey/fire_elemental.png");
	item_textures_copy[22].loadFromFile("standart_games_sp/charodey/lava_golem.png");
	item_textures_copy[23].loadFromFile("standart_games_sp/charodey/ash.png");
	item_textures_copy[24].loadFromFile("standart_games_sp/charodey/lake.png");
	item_textures_copy[25].loadFromFile("standart_games_sp/charodey/silver.png");
	item_textures_copy[26].loadFromFile("standart_games_sp/charodey/swamp_golem.png");
	item_textures_copy[27].loadFromFile("standart_games_sp/charodey/egg.png");
	item_textures_copy[28].loadFromFile("standart_games_sp/charodey/bird.png");
	item_textures_copy[29].loadFromFile("standart_games_sp/charodey/phoenix.png");
	item_textures_copy[30].loadFromFile("standart_games_sp/charodey/golem.png");
	item_textures_copy[31].loadFromFile("standart_games_sp/charodey/human.png");
	item_textures_copy[32].loadFromFile("standart_games_sp/charodey/metal.png");
	item_textures_copy[33].loadFromFile("standart_games_sp/charodey/metal_golem.png");
	item_textures_copy[34].loadFromFile("standart_games_sp/charodey/alcoholic.png");
	item_textures_copy[35].loadFromFile("standart_games_sp/charodey/tool.png");
	item_textures_copy[36].loadFromFile("standart_games_sp/charodey/hut.png");
	item_textures_copy[37].loadFromFile("standart_games_sp/charodey/windstorm.png");
	item_textures_copy[38].loadFromFile("standart_games_sp/charodey/thunderbird.png");
	item_textures_copy[39].loadFromFile("standart_games_sp/charodey/sulfur.png");
	item_textures_copy[40].loadFromFile("standart_games_sp/charodey/plankton.png");
	item_textures_copy[41].loadFromFile("standart_games_sp/charodey/seeds.png");
	item_textures_copy[42].loadFromFile("standart_games_sp/charodey/tree.png");
	item_textures_copy[43].loadFromFile("standart_games_sp/charodey/forest.png");
	item_textures_copy[44].loadFromFile("standart_games_sp/charodey/vulcan.png");
	item_textures_copy[45].loadFromFile("standart_games_sp/charodey/vodka.png");
	item_textures_copy[46].loadFromFile("standart_games_sp/charodey/moss.png");
	item_textures_copy[47].loadFromFile("standart_games_sp/charodey/fern.png");
	item_textures_copy[48].loadFromFile("standart_games_sp/charodey/steam_boiler.png");
	item_textures_copy[49].loadFromFile("standart_games_sp/charodey/aquarium.png");
	item_textures_copy[50].loadFromFile("standart_games_sp/charodey/worm.png");
	item_textures_copy[51].loadFromFile("standart_games_sp/charodey/beetle.png");
	item_textures_copy[52].loadFromFile("standart_games_sp/charodey/butterfly.png");
	item_textures_copy[53].loadFromFile("standart_games_sp/charodey/seashells.png");
	item_textures_copy[54].loadFromFile("standart_games_sp/charodey/fish.png");
	item_textures_copy[55].loadFromFile("standart_games_sp/charodey/river.png");
	item_textures_copy[56].loadFromFile("standart_games_sp/charodey/cancer.png");
	item_textures_copy[57].loadFromFile("standart_games_sp/charodey/hourglass.png");
	item_textures_copy[58].loadFromFile("standart_games_sp/charodey/scarab.png");

	items_list_copy.emplace_back(&item_textures_copy[0], "Fire", "", 1);
	items_list_copy.emplace_back(&item_textures_copy[1], "Water", "", 2);
	items_list_copy.emplace_back(&item_textures_copy[2], "Earth", "", 3);
	items_list_copy.emplace_back(&item_textures_copy[3], "Air", "", 4);
	items_list_copy.emplace_back(&item_textures_copy[4], "Lava", "", 5);
	items_list_copy.emplace_back(&item_textures_copy[5], "Swamp", "", 6);
	items_list_copy.emplace_back(&item_textures_copy[6], "Alcohol", "", 7);
	items_list_copy.emplace_back(&item_textures_copy[7], "Stone", "", 8);
	items_list_copy.emplace_back(&item_textures_copy[8], "Sand", "", 9);
	items_list_copy.emplace_back(&item_textures_copy[9], "Steam", "", 10);
	items_list_copy.emplace_back(&item_textures_copy[10], "Energy", "", 11);
	items_list_copy.emplace_back(&item_textures_copy[11], "Glass", "", 12);
	items_list_copy.emplace_back(&item_textures_copy[12], "Spark", "", 13);
	items_list_copy.emplace_back(&item_textures_copy[13], "Clay", "", 14);
	items_list_copy.emplace_back(&item_textures_copy[14], "Brick", "", 15);
	items_list_copy.emplace_back(&item_textures_copy[15], "Dust", "", 16);
	items_list_copy.emplace_back(&item_textures_copy[16], "Desert", "", 17);
	items_list_copy.emplace_back(&item_textures_copy[17], "Philosopher's Stone", "", 18);
	items_list_copy.emplace_back(&item_textures_copy[18], "Life", "", 19);
	items_list_copy.emplace_back(&item_textures_copy[19], "Bacteria", "", 20);
	items_list_copy.emplace_back(&item_textures_copy[20], "Seaweed", "", 21);
	items_list_copy.emplace_back(&item_textures_copy[21], "Fire Elemental", "", 22);
	items_list_copy.emplace_back(&item_textures_copy[22], "Lava golem", "", 23);
	items_list_copy.emplace_back(&item_textures_copy[23], "Ash", "", 24); // or cinder?
	items_list_copy.emplace_back(&item_textures_copy[24], "Lake", "", 25);
	items_list_copy.emplace_back(&item_textures_copy[25], "Silver", "", 26);
	items_list_copy.emplace_back(&item_textures_copy[26], "Swamp golem", "", 27);
	items_list_copy.emplace_back(&item_textures_copy[27], "Egg", "", 28);
	items_list_copy.emplace_back(&item_textures_copy[28], "Bird", "", 29);
	items_list_copy.emplace_back(&item_textures_copy[29], "Phoenix", "", 30);
	items_list_copy.emplace_back(&item_textures_copy[30], "Golem", "", 31);
	items_list_copy.emplace_back(&item_textures_copy[31], "Human", "", 32);
	items_list_copy.emplace_back(&item_textures_copy[32], "Metal", "", 33);
	items_list_copy.emplace_back(&item_textures_copy[33], "Metal golem", "", 34);
	items_list_copy.emplace_back(&item_textures_copy[34], "Alcoholic", "", 35);
	items_list_copy.emplace_back(&item_textures_copy[35], "Tool", "", 36);
	items_list_copy.emplace_back(&item_textures_copy[36], "Hut", "", 37);
	items_list_copy.emplace_back(&item_textures_copy[37], "Windstorm", "", 38); // or what?
	items_list_copy.emplace_back(&item_textures_copy[38], "Thunderbird", "", 39);
	items_list_copy.emplace_back(&item_textures_copy[39], "Sulfur", "", 40);
	items_list_copy.emplace_back(&item_textures_copy[40], "Plankton", "", 41);
	items_list_copy.emplace_back(&item_textures_copy[41], "Seeds", "", 42);
	items_list_copy.emplace_back(&item_textures_copy[42], "Tree", "", 43);
	items_list_copy.emplace_back(&item_textures_copy[43], "Forest", "", 44);
	items_list_copy.emplace_back(&item_textures_copy[44], "Vulcan", "", 45);
	items_list_copy.emplace_back(&item_textures_copy[45], "Vodka", "", 46);
	items_list_copy.emplace_back(&item_textures_copy[46], "Moss", "", 47);
	items_list_copy.emplace_back(&item_textures_copy[47], "Fern", "", 48);
	items_list_copy.emplace_back(&item_textures_copy[48], "Steam boiler", "", 49);
	items_list_copy.emplace_back("Dirt", "", 50, EARTH_COLOR);
	items_list_copy.emplace_back(&item_textures_copy[49], "Aquarium", "", 51);
	items_list_copy.emplace_back(&item_textures_copy[50], "Worm", "", 52);
	items_list_copy.emplace_back(&item_textures_copy[51], "Beetle", "", 53);
	items_list_copy.emplace_back(&item_textures_copy[52], "Butterfly", "", 54);
	items_list_copy.emplace_back(&item_textures_copy[53], "Seashells", "", 55);
	items_list_copy.emplace_back(&item_textures_copy[54], "Fish", "", 56);
	items_list_copy.emplace_back(&item_textures_copy[55], "River", "", 57);
	items_list_copy.emplace_back(&item_textures_copy[56], "Cancer", "", 58);
	items_list_copy.emplace_back(&item_textures_copy[57], "Hourglass", "", 59);
	items_list_copy.emplace_back(&item_textures_copy[58], "Scarab", "", 60);

	reactions_list_copy.push_back(Reaction({1, 2}, std::vector<unsigned int>{7})); // fire+water=alcohol
	reactions_list_copy.push_back(Reaction({1, 3}, std::vector<unsigned int>{5})); // fire+earth=lava
	reactions_list_copy.push_back(Reaction({1, 4}, std::vector<unsigned int>{11})); // fire+air=energy
	reactions_list_copy.push_back(Reaction({1, 7}, std::vector<unsigned int>{11})); // fire+alcohol=energy
	reactions_list_copy.push_back(Reaction({2, 5}, std::vector<unsigned int>{8, 10})); // water+lava=stone+steam
	reactions_list_copy.push_back(Reaction({3, 4}, std::vector<unsigned int>{16})); // earth+air=dust
	reactions_list_copy.push_back(Reaction({4, 5}, std::vector<unsigned int>{8})); // air+lava=stone
	reactions_list_copy.push_back(Reaction({2, 3}, std::vector<unsigned int>{6})); // water+earth=swamp
	reactions_list_copy.push_back(Reaction({2, 4}, std::vector<unsigned int>{10})); // water+air=steam
	reactions_list_copy.push_back(Reaction({2, 8}, std::vector<unsigned int>{9})); // water+stone=sand
	reactions_list_copy.push_back(Reaction({1, 9}, std::vector<unsigned int>{12})); // fire+sand=glass
	reactions_list_copy.push_back(Reaction({8, 8}, std::vector<unsigned int>{8, 8, 13})); // stone+stone=stone+stone+spark
	reactions_list_copy.push_back(Reaction({6, 9}, std::vector<unsigned int>{14})); // swamp+sand=clay
	reactions_list_copy.push_back(Reaction({1, 14}, std::vector<unsigned int>{15})); // fire+clay=brick
	reactions_list_copy.push_back(Reaction({3, 9}, std::vector<unsigned int>{17})); // earth+sand=desert
	reactions_list_copy.push_back(Reaction({8, 11}, std::vector<unsigned int>{18})); // stone+energy=philosopher's stone
	reactions_list_copy.push_back(Reaction({6, 11}, std::vector<unsigned int>{19})); // swamp+energy=life
	reactions_list_copy.push_back(Reaction({6, 19}, std::vector<unsigned int>{20})); // swamp+life=bacteria
	reactions_list_copy.push_back(Reaction({2, 19}, std::vector<unsigned int>{21})); // water+life=seaweed
	reactions_list_copy.push_back(Reaction({1, 19}, std::vector<unsigned int>{22})); // fire+life=fire_elemental
	reactions_list_copy.push_back(Reaction({5, 19}, std::vector<unsigned int>{23})); // lava+life=lava_golem
	reactions_list_copy.push_back(Reaction({2, 22}, std::vector<unsigned int>{24, 24, 11, 11, 11, 10})); // fire elemental+water=energy+energy+energy+steam+ash+ash
	reactions_list_copy.push_back(Reaction({2, 2}, std::vector<unsigned int>{25})); // water+water=lake
	reactions_list_copy.push_back(Reaction({5, 10}, std::vector<unsigned int>{26})); // lava+steam=silver
	reactions_list_copy.push_back(Reaction({1, 6}, std::vector<unsigned int>{27})); // fire+swamp=swamp golem
	reactions_list_copy.push_back(Reaction({8, 19}, std::vector<unsigned int>{28})); // stone+life=egg
	reactions_list_copy.push_back(Reaction({4, 28}, std::vector<unsigned int>{29})); // air+egg=bird
	reactions_list_copy.push_back(Reaction({1, 29}, std::vector<unsigned int>{30}));  // fire+bird=phoenix
	reactions_list_copy.push_back(Reaction({14, 19}, std::vector<unsigned int>{31}));  // clay+life=golem
	reactions_list_copy.push_back(Reaction({14, 31}, std::vector<unsigned int>{32}));  // life+golem=human
	reactions_list_copy.push_back(Reaction({1, 8}, std::vector<unsigned int>{33}));  // fire+stone=metal
	reactions_list_copy.push_back(Reaction({19, 33}, std::vector<unsigned int>{34}));  // life+metal=metal golem
	reactions_list_copy.push_back(Reaction({7, 32}, std::vector<unsigned int>{35}));  // alcohol+human=alcoholic
	reactions_list_copy.push_back(Reaction({32, 33}, std::vector<unsigned int>{36}));  // matal+human=tool
	reactions_list_copy.push_back(Reaction({8, 32}, std::vector<unsigned int>{37}));  // stone+human=hut
	reactions_list_copy.push_back(Reaction({19, 33}, std::vector<unsigned int>{34}));  // life+metal=metal golem
	reactions_list_copy.push_back(Reaction({7, 32}, std::vector<unsigned int>{35}));  // alcohol+human=alcoholic
	reactions_list_copy.push_back(Reaction({32, 33}, std::vector<unsigned int>{36}));  // matal+human=tool
	reactions_list_copy.push_back(Reaction({8, 32}, std::vector<unsigned int>{37}));  // stone+human=hut
	reactions_list_copy.push_back(Reaction({4, 11}, std::vector<unsigned int>{38}));  // air+energy=windstorm
	reactions_list_copy.push_back(Reaction({29, 38}, std::vector<unsigned int>{39}));  // bird+windstorm=thunderbird
	reactions_list_copy.push_back(Reaction({6, 20}, std::vector<unsigned int>{40}));  // swamp+bacteria=sulfur
	reactions_list_copy.push_back(Reaction({2, 20}, std::vector<unsigned int>{41}));  // water+bacteria=plankton
	reactions_list_copy.push_back(Reaction({9, 19}, std::vector<unsigned int>{42}));  // sand+life=seeds
	reactions_list_copy.push_back(Reaction({3, 42}, std::vector<unsigned int>{43}));  // earth+seeds=tree
	reactions_list_copy.push_back(Reaction({43, 43}, std::vector<unsigned int>{44}));  // tree+tree=forest
	reactions_list_copy.push_back(Reaction({3, 5}, std::vector<unsigned int>{45}));  // earth+lava=vulcan
	reactions_list_copy.push_back(Reaction({2, 7}, std::vector<unsigned int>{46}));  // water+alcohol=vodka
	reactions_list_copy.push_back(Reaction({6, 21}, std::vector<unsigned int>{47}));  // swamp+seaweed=moss
	reactions_list_copy.push_back(Reaction({6, 47}, std::vector<unsigned int>{48}));  // swamp+moss=fern
	reactions_list_copy.push_back(Reaction({10, 33}, std::vector<unsigned int>{49}));  // steam+metal=steam boiler
	reactions_list_copy.push_back(Reaction({2, 16}, std::vector<unsigned int>{50}));  // water+dust=dirt
	reactions_list_copy.push_back(Reaction({2, 12}, std::vector<unsigned int>{51}));  // water+glass=aquarium
	reactions_list_copy.push_back(Reaction({3, 41}, std::vector<unsigned int>{52}));  // earth+plankron=worm
	reactions_list_copy.push_back(Reaction({3, 52}, std::vector<unsigned int>{53}));  // earth+worm=beetle
	reactions_list_copy.push_back(Reaction({4, 52}, std::vector<unsigned int>{54}));  // air+worm=butterfly
	reactions_list_copy.push_back(Reaction({8, 41}, std::vector<unsigned int>{55}));  // stone+seashells=butterfly
	reactions_list_copy.push_back(Reaction({20, 41}, std::vector<unsigned int>{56}));  // bacteria+plankton=fish
	reactions_list_copy.push_back(Reaction({2, 25}, std::vector<unsigned int>{57}));  // water+lake=river
	reactions_list_copy.push_back(Reaction({41, 57}, std::vector<unsigned int>{58}));  // plankton+river=cancer
	reactions_list_copy.push_back(Reaction({9, 12}, std::vector<unsigned int>{59}));  // sand+glass=hourglass
	reactions_list_copy.push_back(Reaction({17, 53}, std::vector<unsigned int>{60}));  // desert+beetle=scarab

	started_items_copy.push_back(Reagent({1, false}));
	started_items_copy.push_back(Reagent({2, false}));
	started_items_copy.push_back(Reagent({3, false}));
	started_items_copy.push_back(Reagent({4, false}));
}
