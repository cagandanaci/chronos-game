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


template <typename Resource, typename Identifier>
class ResourceManager
{
public:
	void							load(Identifier id, const std::string& filename);

	Resource&						get(Identifier id);
	const Resource&					get(Identifier id) const;

private:
	std::map<Identifier, 
		std::unique_ptr<Resource>>	mResourceMap;
};

// Implementations

template<typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	auto resource = std::make_unique<Resource>(filename);

	auto inserted = mResourceMap.insert({ id, std::move(resource) });
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	return *mResourceMap.at(id);
}

template<typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	return *mResourceMap.at(id);
}

// Aliases

using TextureManager = ResourceManager<sf::Texture, TextureID>;

using FontManager = ResourceManager<sf::Font, FontID>;

template <typename Identifier>
using SoundBufferManager = ResourceManager<sf::SoundBuffer, Identifier>;

template <typename Identifier>
using MusicManager = ResourceManager<sf::Music, Identifier>;
