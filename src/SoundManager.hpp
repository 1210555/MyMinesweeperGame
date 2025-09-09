#ifndef SOUNDMANAGER_HPP
#define SOUNDOANAGER_HPP
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {
public:
    SoundManager();
    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);

private:
    std::map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::vector<sf::Sound> m_sounds; // 複数の音を同時に鳴らすため
};
#endif