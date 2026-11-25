#pragma once
// The includes aren't needed as all of them are included in PCH (delete this comment after seeing it.

// TODO(Mustafa):
//
// 1. Use English comments instead of Turkish ones.
// 2. Create a non-default constructor for the animation clip.
// 3. Instead of names, consider using IDs that are stored inside the Animation Clip struct.
// 4. (IMPORTANT) Use enum classes instead of strings for animation clip names/IDs.
// 5. (IMPORTANT) A temporary struct is added in World.h for testing the animation with 
//	  a sprite that uses "character-sheet.png" texture. Use it for testing.
//

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

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	std::unordered_map<std::string, AnimationClip> mClips;

	std::string mCurrentClip;
	int mCurrentFrame = 0;

	sf::Time mElapsedTime = sf::Time::Zero;

	bool mFinished = false;
};