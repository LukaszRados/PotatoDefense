/*
  pausableclock
  Copyright (C) 2009 Marco Antognini (hiura@romandie.com)
  License : CC-BY-SA 3.0
        You can find the full legal code at
        http://creativecommons.org/licenses/by-sa/3.0/
        or in the local file cc-by-sa-3.0-legalcode.html .
        Here is only an abstract :

  You are free :
        to Share — to copy, distribute and transmit the work
        to Remix — to adapt the work

  Under the following conditions :
        Attribution. You must attribute the work in the manner
                specified by the author or licensor (but not
                in any way that suggests that they endorse you
                or your use of the work).
        Share Alike. If you alter, transform, or build upon this
                work, you may distribute the resulting work only
                under the same, similar or a compatible license.

  For any reuse or distribution, you must make clear to others
        the license terms of this work. The best way to do this
        is with a link to this
        (http://creativecommons.org/licenses/by-sa/3.0/) web page.

  Any of the above conditions can be waived if you get
        permission from the copyright holder.

  Nothing in this license impairs or restricts the author's
        moral rights.

  SPECIAL THANKS TO SFML LIBRARY (See http://sfml-dev.org)
  AND to Laurent Gomila.
*/



#ifndef PAUSABLECLOCK_HPP
#define PAUSABLECLOCK_HPP

#include <SFML/System.hpp>

/**
 * \class PuasableClock
 * \brief Zegar, ktory mozna zatrzymac i wznowic
 *
 * Klasa opakowuje zwykly sf::Clock i dodaje do niego funkcje pause(),start() oraz isPaused(). Zostala stworzona na podstawie PausableClock autorstwa Marco Antognini,
 * jednak zostala dostosowana do wersji 2.0 biblioteki SFML, usunieto przestrzen nazw oraz dodano funkcje isPaused().
 */
class PausableClock
{
        public :
			/**
			 * Konstruktor domyslny
			 */
			PausableClock(bool paused = false)
                : am_i_paused(paused)
                {
                }
			/**
			 * Procedura zatrzymujaca zegar
			 */
                void pause(void)
                {
                        // If not yet paused...
                        if (!am_i_paused)
                        {
                                am_i_paused = true;
                                my_time += my_clock.getElapsedTime();
                        }
                }

                /**
                 * Procedura wznawiajaca zegar
                 */
                void start(void)
                {
                        // If not yet started...
                        if (am_i_paused)
                        {
                                my_clock.restart();
                                am_i_paused = false;
                        }
                }

                /**
                 * Funckja zwracajaca czas od ostatniego wywolanaia funkcji restart() lub konstruktora ( z wylaczeniem czasu, gdy zegar byl zatrzymany).
                 * \return sf::Time czas od ostatniego restartu
                 */
                sf::Time getElapsedTime(void) const
                {
                        // If not paused...
                        if (!am_i_paused)
                                return my_time + my_clock.getElapsedTime();
                        else
                                return my_time;
                }

                /**
                 * Procedura restartowania zegara
                 */
                void restart(bool paused = false)
                {
                        am_i_paused = paused;
                        my_time = sf::seconds(0);
                        my_clock.restart();
                }

                /**
                 * Procedura sprawdzajaca czy zegar jest zatrzymany
                 * \return true Jesli zegar jest zatrzymany
                 * \return false Jesli zegar nie jest zatrzymany
                 */
                bool isPaused(void) const{
                	return am_i_paused;
                }
        private :
                bool am_i_paused;
                sf::Time my_time;
                sf::Clock my_clock;
};


#endif // PAUSABLECLOCK_HPP
