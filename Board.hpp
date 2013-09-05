#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Clickable.hpp"
#include "Wall.hpp"
#include "GameState.hpp"
/**
 * \mainpage
 * Gra PotatoDefense zostala stworzona przy pomocy biblioteki SFML 2.0. Jej tworcami sa: Lukasz Rados oraz Krzysztof Skowronek.
 */




/**
 * \class Board
* \brief Klasa-kontener na plansze do gry.
*
 * Klasa Board reprezentujaca plansze do gry. W niej zawiera sie m.in. obiekt klasy sf::RenderWindow sluzacy do wyswietlania grafiki.
 */
class Board {
public:
	/**
	 * Procedura inicjujaca klase Board. Tworzy obiekt sf::RenderWindow, a także wypełnia tablice board.
	 */
	static void init();
	/**
	 * Procedura czyszczaca klase Board, odpowiednik statycznego "destruktora".
	 */
	static void deinit();
	/**
	 * Procedura tworzaca plik autosave.pf, ktory zawiera stan gry po danej fali i pozwala na jego odtworzenie.
	 */
	static void save();

	/**
	 * Funkcja zwracajaca tablice wiez znajdujacych sie na planszy, wykorzystywana do obliczania sciezki dla robali.
	 * \return Tablica wiez w reprezentacji liczb calkowitych
	 */
	static std::vector<std::vector<int>>  getBoardAsInts();

	static std::vector<std::vector<Clickable*>> board;
	static sf::RenderWindow* window;
	static Clickable* buffer;
	static int width;
	static int height;
	static int fieldW;
	static int fieldH;
};

#endif /* BOARD_HPP_ */
