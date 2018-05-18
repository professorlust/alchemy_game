#include "Charodey.hpp"

Charodey::Charodey()
{
	initialization_textures();
	initialization_elements();
	initialization_reactions();
	initialization_started_elements();

	number_of_elements = element_list.size();
	number_of_reactions = reactions_list.size();

	name = "Charodey";
	author = "default";
	description = "Standard test game. FOR THIS TIME IS NOT FINISHED\nYa inglish-man *blacksun*";
}

Charodey::~Charodey()
{

}

void Charodey::initialization_textures()
{
	int number_of_textures = 60;
	for (int i = 0; i < number_of_textures; ++i)
	{
		textures.push_back(new sf::Texture());
	}

	textures[0]->loadFromFile("standart_games_sp/charodey/fire.png");
	textures[1]->loadFromFile("standart_games_sp/charodey/water.png");
	textures[2]->loadFromFile("standart_games_sp/charodey/earth.png");
	textures[3]->loadFromFile("standart_games_sp/charodey/air.png");
	textures[4]->loadFromFile("standart_games_sp/charodey/lava.png");
	textures[5]->loadFromFile("standart_games_sp/charodey/swamp.png");
	textures[6]->loadFromFile("standart_games_sp/charodey/alcohol.png");
	textures[7]->loadFromFile("standart_games_sp/charodey/stone.png");
	textures[8]->loadFromFile("standart_games_sp/charodey/sand.png");
	textures[9]->loadFromFile("standart_games_sp/charodey/steam.png");
	textures[10]->loadFromFile("standart_games_sp/charodey/energy.png");
	textures[11]->loadFromFile("standart_games_sp/charodey/glass.png");
	textures[12]->loadFromFile("standart_games_sp/charodey/spark.png");
	textures[13]->loadFromFile("standart_games_sp/charodey/clay.png");
	textures[14]->loadFromFile("standart_games_sp/charodey/brick.png");
	textures[15]->loadFromFile("standart_games_sp/charodey/dust.png");
	textures[16]->loadFromFile("standart_games_sp/charodey/desert.png");
	textures[17]->loadFromFile("standart_games_sp/charodey/philosophers_stone.png");
	textures[18]->loadFromFile("standart_games_sp/charodey/life.png");
	textures[19]->loadFromFile("standart_games_sp/charodey/bacteria.png");
	textures[20]->loadFromFile("standart_games_sp/charodey/seaweed.png");
	textures[21]->loadFromFile("standart_games_sp/charodey/fire_elemental.png");
	textures[22]->loadFromFile("standart_games_sp/charodey/lava_golem.png");
	textures[23]->loadFromFile("standart_games_sp/charodey/ash.png");
	textures[24]->loadFromFile("standart_games_sp/charodey/lake.png");
	textures[25]->loadFromFile("standart_games_sp/charodey/silver.png");
	textures[26]->loadFromFile("standart_games_sp/charodey/swamp_golem.png");
	textures[27]->loadFromFile("standart_games_sp/charodey/egg.png");
	textures[28]->loadFromFile("standart_games_sp/charodey/bird.png");
	textures[29]->loadFromFile("standart_games_sp/charodey/phoenix.png");
	textures[30]->loadFromFile("standart_games_sp/charodey/golem.png");
	textures[31]->loadFromFile("standart_games_sp/charodey/human.png");
	textures[32]->loadFromFile("standart_games_sp/charodey/metal.png");
	textures[33]->loadFromFile("standart_games_sp/charodey/metal_golem.png");
	textures[34]->loadFromFile("standart_games_sp/charodey/alcoholic.png");
	textures[35]->loadFromFile("standart_games_sp/charodey/tool.png");
	textures[36]->loadFromFile("standart_games_sp/charodey/hut.png");
	textures[37]->loadFromFile("standart_games_sp/charodey/windstorm.png");
	textures[38]->loadFromFile("standart_games_sp/charodey/thunderbird.png");
	textures[39]->loadFromFile("standart_games_sp/charodey/sulfur.png");
	textures[40]->loadFromFile("standart_games_sp/charodey/plankton.png");
	textures[41]->loadFromFile("standart_games_sp/charodey/seeds.png");
	textures[42]->loadFromFile("standart_games_sp/charodey/tree.png");
	textures[43]->loadFromFile("standart_games_sp/charodey/forest.png");
	textures[44]->loadFromFile("standart_games_sp/charodey/vulcan.png");
	textures[45]->loadFromFile("standart_games_sp/charodey/vodka.png");
	textures[46]->loadFromFile("standart_games_sp/charodey/moss.png");
	textures[47]->loadFromFile("standart_games_sp/charodey/fern.png");
	textures[48]->loadFromFile("standart_games_sp/charodey/steam_boiler.png");
	textures[49]->loadFromFile("standart_games_sp/charodey/aquarium.png");
	textures[50]->loadFromFile("standart_games_sp/charodey/worm.png");
	textures[51]->loadFromFile("standart_games_sp/charodey/beetle.png");
	textures[52]->loadFromFile("standart_games_sp/charodey/butterfly.png");
	textures[53]->loadFromFile("standart_games_sp/charodey/seashells.png");
	textures[54]->loadFromFile("standart_games_sp/charodey/fish.png");
	textures[55]->loadFromFile("standart_games_sp/charodey/river.png");
	textures[56]->loadFromFile("standart_games_sp/charodey/cancer.png");
	textures[57]->loadFromFile("standart_games_sp/charodey/hourglass.png");
	textures[58]->loadFromFile("standart_games_sp/charodey/scarab.png");
	}

void Charodey::initialization_elements()
{
	element_list.emplace_back(textures[0], "Fire", "", 1);
	element_list.emplace_back(textures[1], "Water", "", 2);
	element_list.emplace_back(textures[2], "Earth", "", 3);
	element_list.emplace_back(textures[3], "Air", "", 4);
	element_list.emplace_back(textures[4], "Lava", "", 5);
	element_list.emplace_back(textures[5], "Swamp", "", 6);
	element_list.emplace_back(textures[6], "Alcohol", "", 7);
	element_list.emplace_back(textures[7], "Stone", "", 8);
	element_list.emplace_back(textures[8], "Sand", "", 9);
	element_list.emplace_back(textures[9], "Steam", "", 10);
	element_list.emplace_back(textures[10], "Energy", "", 11);
	element_list.emplace_back(textures[11], "Glass", "", 12);
	element_list.emplace_back(textures[12], "Spark", "", 13);
	element_list.emplace_back(textures[13], "Clay", "", 14);
	element_list.emplace_back(textures[14], "Brick", "", 15);
	element_list.emplace_back(textures[15], "Dust", "", 16);
	element_list.emplace_back(textures[16], "Desert", "", 17);
	element_list.emplace_back(textures[17], "Philosopher's Stone", "", 18);
	element_list.emplace_back(textures[18], "Life", "", 19);
	element_list.emplace_back(textures[19], "Bacteria", "", 20);
	element_list.emplace_back(textures[20], "Seaweed", "", 21);
	element_list.emplace_back(textures[21], "Fire Elemental", "", 22);
	element_list.emplace_back(textures[22], "Lava golem", "", 23);
	element_list.emplace_back(textures[23], "Ash", "", 24); // or cinder?
	element_list.emplace_back(textures[24], "Lake", "", 25);
	element_list.emplace_back(textures[25], "Silver", "", 26);
	element_list.emplace_back(textures[26], "Swamp golem", "", 27);
	element_list.emplace_back(textures[27], "Egg", "", 28);
	element_list.emplace_back(textures[28], "Bird", "", 29);
	element_list.emplace_back(textures[29], "Phoenix", "", 30);
	element_list.emplace_back(textures[30], "Golem", "", 31);
	element_list.emplace_back(textures[31], "Human", "", 32);
	element_list.emplace_back(textures[32], "Metal", "", 33);
	element_list.emplace_back(textures[33], "Metal golem", "", 34);
	element_list.emplace_back(textures[34], "Alcoholic", "", 35);
	element_list.emplace_back(textures[35], "Tool", "", 36);
	element_list.emplace_back(textures[36], "Hut", "", 37);
	element_list.emplace_back(textures[37], "Windstorm", "", 38); // or what?
	element_list.emplace_back(textures[38], "Thunderbird", "", 39);
	element_list.emplace_back(textures[39], "Sulfur", "", 40);
	element_list.emplace_back(textures[40], "Plankton", "", 41);
	element_list.emplace_back(textures[41], "Seeds", "", 42);
	element_list.emplace_back(textures[42], "Tree", "", 43);
	element_list.emplace_back(textures[43], "Forest", "", 44);
	element_list.emplace_back(textures[44], "Vulcan", "", 45);
	element_list.emplace_back(textures[45], "Vodka", "", 46);
	element_list.emplace_back(textures[46], "Moss", "", 47);
	element_list.emplace_back(textures[47], "Fern", "", 48);
	element_list.emplace_back(textures[48], "Steam boiler", "", 49);
	element_list.emplace_back("Dirt", "", 50, EARTH_COLOR);
	element_list.emplace_back(textures[49], "Aquarium", "", 51);
	element_list.emplace_back(textures[50], "Worm", "", 52);
	element_list.emplace_back(textures[51], "Beetle", "", 53);
	element_list.emplace_back(textures[52], "Butterfly", "", 54);
	element_list.emplace_back(textures[53], "Seashells", "", 55);
	element_list.emplace_back(textures[54], "Fish", "", 56);
	element_list.emplace_back(textures[55], "River", "", 57);
	element_list.emplace_back(textures[56], "Cancer", "", 58);
	element_list.emplace_back(textures[57], "Hourglass", "", 59);
	element_list.emplace_back(textures[58], "Scarab", "", 60);
}

void Charodey::initialization_reactions()
{
	reactions_list.push_back(Reaction({1, 2}, {7})); // fire+water=alcohol
	reactions_list.push_back(Reaction({1, 3}, {5})); // fire+earth=lava
	reactions_list.push_back(Reaction({1, 4}, {11})); // fire+air=energy
	reactions_list.push_back(Reaction({1, 7}, {11})); // fire+alcohol=energy
	reactions_list.push_back(Reaction({2, 5}, {8, 10})); // water+lava=stone+steam
	reactions_list.push_back(Reaction({3, 4}, {16})); // earth+air=dust
	reactions_list.push_back(Reaction({4, 5}, {8})); // air+lava=stone
	reactions_list.push_back(Reaction({2, 3}, {6})); // water+earth=swamp
	reactions_list.push_back(Reaction({2, 4}, {10})); // water+air=steam
	reactions_list.push_back(Reaction({2, 8}, {9})); // water+stone=sand
	reactions_list.push_back(Reaction({1, 9}, {12})); // fire+sand=glass
	reactions_list.push_back(Reaction({8, 8}, {8, 8, 13})); // stone+stone=stone+stone+spark
	reactions_list.push_back(Reaction({6, 9}, {14})); // swamp+sand=clay
	reactions_list.push_back(Reaction({1, 14}, {15})); // fire+clay=brick
	reactions_list.push_back(Reaction({3, 9}, {17})); // earth+sand=desert
	reactions_list.push_back(Reaction({8, 11}, {18})); // stone+energy=philosopher's stone
	reactions_list.push_back(Reaction({6, 11}, {19})); // swamp+energy=life
	reactions_list.push_back(Reaction({6, 19}, {20})); // swamp+life=bacteria
	reactions_list.push_back(Reaction({2, 19}, {21})); // water+life=seaweed
	reactions_list.push_back(Reaction({1, 19}, {22})); // fire+life=fire_elemental
	reactions_list.push_back(Reaction({5, 19}, {23})); // lava+life=lava_golem
	reactions_list.push_back(Reaction({2, 22}, {24, 24, 11, 11, 11, 10})); // fire elemental+water=energy+energy+energy+steam+ash+ash
	reactions_list.push_back(Reaction({2, 2}, {25})); // water+water=lake
	reactions_list.push_back(Reaction({5, 10}, {26})); // lava+steam=silver
	reactions_list.push_back(Reaction({1, 6}, {27})); // fire+swamp=swamp golem
	reactions_list.push_back(Reaction({8, 19}, {28})); // stone+life=egg
	reactions_list.push_back(Reaction({4, 28}, {29})); // air+egg=bird
	reactions_list.push_back(Reaction({1, 29}, {30}));  // fire+bird=phoenix
	reactions_list.push_back(Reaction({14, 19}, {31}));  // clay+life=golem
	reactions_list.push_back(Reaction({14, 31}, {32}));  // life+golem=human
	reactions_list.push_back(Reaction({1, 8}, {33}));  // fire+stone=metal
	reactions_list.push_back(Reaction({19, 33}, {34}));  // life+metal=metal golem
	reactions_list.push_back(Reaction({7, 32}, {35}));  // alcohol+human=alcoholic
	reactions_list.push_back(Reaction({32, 33}, {36}));  // matal+human=tool
	reactions_list.push_back(Reaction({8, 32}, {37}));  // stone+human=hut
	reactions_list.push_back(Reaction({19, 33}, {34}));  // life+metal=metal golem
	reactions_list.push_back(Reaction({7, 32}, {35}));  // alcohol+human=alcoholic
	reactions_list.push_back(Reaction({32, 33}, {36}));  // matal+human=tool
	reactions_list.push_back(Reaction({8, 32}, {37}));  // stone+human=hut
	reactions_list.push_back(Reaction({4, 11}, {38}));  // air+energy=windstorm
	reactions_list.push_back(Reaction({29, 38}, {39}));  // bird+windstorm=thunderbird
	reactions_list.push_back(Reaction({6, 20}, {40}));  // swamp+bacteria=sulfur
	reactions_list.push_back(Reaction({2, 20}, {41}));  // water+bacteria=plankton
	reactions_list.push_back(Reaction({9, 19}, {42}));  // sand+life=seeds
	reactions_list.push_back(Reaction({3, 42}, {43}));  // earth+seeds=tree
	reactions_list.push_back(Reaction({43, 43}, {44}));  // tree+tree=forest
	reactions_list.push_back(Reaction({3, 5}, {45}));  // earth+lava=vulcan
	reactions_list.push_back(Reaction({2, 7}, {46}));  // water+alcohol=vodka
	reactions_list.push_back(Reaction({6, 21}, {47}));  // swamp+seaweed=moss
	reactions_list.push_back(Reaction({6, 47}, {48}));  // swamp+moss=fern
	reactions_list.push_back(Reaction({10, 33}, {49}));  // steam+metal=steam boiler
	reactions_list.push_back(Reaction({2, 16}, {50}));  // water+dust=dirt
	reactions_list.push_back(Reaction({2, 12}, {51}));  // water+glass=aquarium
	reactions_list.push_back(Reaction({3, 41}, {52}));  // earth+plankron=worm
	reactions_list.push_back(Reaction({3, 52}, {53}));  // earth+worm=beetle
	reactions_list.push_back(Reaction({4, 52}, {54}));  // air+worm=butterfly
	reactions_list.push_back(Reaction({8, 41}, {55}));  // stone+seashells=butterfly
	reactions_list.push_back(Reaction({20, 41}, {56}));  // bacteria+plankton=fish
	reactions_list.push_back(Reaction({2, 25}, {57}));  // water+lake=river
	reactions_list.push_back(Reaction({41, 57}, {58}));  // plankton+river=cancer
	reactions_list.push_back(Reaction({9, 12}, {59}));  // sand+glass=hourglass
	reactions_list.push_back(Reaction({17, 53}, {60}));  // desert+beetle=scarab
}

void Charodey::initialization_started_elements()
{
	started_elements.push_back(1);
	started_elements.push_back(2);
	started_elements.push_back(3);
	started_elements.push_back(4);
}
