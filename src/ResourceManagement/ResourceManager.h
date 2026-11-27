#pragma once

enum class TextureID
{
	MenuBackground,
	Background,
	Player
};
enum class FontID
{
	PixelOp
};

/*
*===============================================================
*				RESOURCE MANAGER TEMPLATE CLASS
*===============================================================
*/

// This class stores the game's resources and provides access to them.

template <typename Resource, typename ID>
class ResourceManager
{
public:
	void load(ID id, const std::string& filepath);
	Resource& get(ID id);
	const Resource& get(ID id) const;

private:
	std::unordered_map<ID, std::unique_ptr<Resource>> mResourceList;
};


// Implementations

template<typename Resource, typename ID>
inline void ResourceManager<Resource, ID>::load(ID id, const std::string& filepath)
{
	auto resource = std::make_unique<Resource>(filepath);
	auto inserted = mResourceList.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename ID>
inline Resource& ResourceManager<Resource,ID>::get(ID id)
{
	auto found = mResourceList.find(id);
	assert(found != mResourceList.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceList.find(id);
	assert(found != mResourceList.end());

	return *found->second;
}

// Aliases

using TextureManager = ResourceManager<sf::Texture, TextureID>;

using FontManager = ResourceManager<sf::Font, FontID>;

template <typename Identifier>
using SoundBufferManager = ResourceManager<sf::SoundBuffer, Identifier>;

template <typename Identifier>
using MusicManager = ResourceManager<sf::Music, Identifier>;
