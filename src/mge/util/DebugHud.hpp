#ifndef DEBUGHUD_HPP
#define DEBUGHUD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class DebugHud
{
	public:
		DebugHud( sf::RenderWindow * aWindow );
		virtual ~DebugHud();
		void draw();

		void setDebugInfo (std::string pInfo);
        void setObjectsInfo(std::string pInfo);

	private:
		sf::RenderWindow * _window;

        std::string _debugInfo;

        sf::Font _font;
        sf::Text _debugText;
        sf::Text _objectText;

        void _createDebugHud();
        void _createObjectsHud();

        DebugHud(const DebugHud&);
        DebugHud& operator=(const DebugHud&);

};

#endif // DEBUGHUD_HPP
