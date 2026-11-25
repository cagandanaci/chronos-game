#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>

struct AnimationClip
{
	sf::Vector2i startPosition; // Sprite sheet üzerindeki başlangıç (x, y) pikseli
	sf::Vector2i frameSize;     // Tek bir karenin (genişlik, yükseklik) boyutu
	int frameCount = 1;         // Klipteki toplam kare sayısı
	sf::Time duration;          // Kareler arası geçiş süresi
	bool isLooping = true;      // Sona gelince başa sarsın mı?
};

class AnimationComponent
{
public:
	AnimationComponent() = default;

	// Yeni bir animasyon klibi (örneğin "Idle", "Run", "Attack") ekler
	void addClip(const std::string& name, const AnimationClip& clip);

	// Belirtilen klibi başlatır (zaten oynuyorsa sıfırlamaz)
	void play(const std::string& name, bool resetIfSame = false);

	// Süreyi günceller, gerekirse sonraki kareye geçer ve güncel sf::IntRect döndürür
	sf::IntRect update(sf::Time dt);

	// Update çağırmadan o anki karenin dikdörtgenini almak için
	sf::IntRect getCurrentFrameRect() const;

	bool isFinished() const;
	const std::string& getCurrentClipName() const;

private:
	std::unordered_map<std::string, AnimationClip> mClips;
	std::string mCurrentClip;
	int mCurrentFrame = 0;
	sf::Time mElapsedTime = sf::Time::Zero;
	bool mFinished = false;
};