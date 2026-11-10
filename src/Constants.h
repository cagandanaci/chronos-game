#pragma once

// Game

inline constexpr sf::Time TIME_PER_FRAME		= sf::seconds(1/60.f);	// 60 FPS

// Window

inline constexpr unsigned WINDOW_WIDTH			= 800;
inline constexpr unsigned WINDOW_HEIGHT			= 600;

// World

inline constexpr sf::Vector2f BOUNDS_SIZE		= {WINDOW_WIDTH * 3, WINDOW_HEIGHT};
inline constexpr sf::Vector2f SPAWN_POSITION	= {200.f, 400.f};

// Player

inline constexpr float MIN_PLAYER_SPEED							= 200.f;
inline constexpr float DEFAULT_HORIZONTAL_PLAYER_ACCELERATION	= 4000.f;	// TOP SPEED = ACCELERATION / FPS * (1 - DRAG), FPS is updates per second.
inline constexpr float DEFAULT_VERTICAL_PLAYER_ACCELERATION		= 38000.f;	

// Physics

inline constexpr float DRAG	= 0.9f;
inline constexpr float GRAVITY = 1200.f;
