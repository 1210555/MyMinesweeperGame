#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager() {
    m_sounds.resize(10); // 同時に鳴らせる音の数を10個に設定
}

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound file: " << filename << std::endl;
        return;
    }
    m_soundBuffers[name] = buffer;
}

void SoundManager::playSound(const std::string& name) {
    // 再生中でないSoundオブジェクトを探す
    for (auto& sound : m_sounds) {
        if (sound.getStatus() != sf::Sound::Playing) {
            sound.setBuffer(m_soundBuffers[name]);
            sound.play();
            return; // 1回鳴らしたら終了
        }
    }
}