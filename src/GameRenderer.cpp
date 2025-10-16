#include "GameRenderer.hpp"
#include <iostream>

GameRenderer::GameRenderer(int offset) : uiOffset(offset){
    // テクスチャファイルへパスを定義
    std::map<std::string, std::string> files={
        {"white","assets/pictures/GroundWhite.jpg"},
        {"flag", "assets/pictures/Flag2.png"},
        {"mine","assets/pictures/bomb.png"},
        //{"boom","assets/pictures/bomb.png"}
    };

    // 全てのテクスチャをループで読み込み、textures マップに格納
    for(const auto& pair : files){
        sf::Texture texture;
        if(!texture.loadFromFile(pair.second)){//パスにアクセス
            std::cerr << "Error loading texture: " << pair.second << std::endl;
        }
        textures.emplace(pair.first, std::move(texture));//キーにアクセス
    }
}

void GameRenderer::display(sf::RenderWindow& window, int tileSize, GameState currentState, const sf::Font& font, const Field& field, const std::vector<std::vector<bool>>& opened, const std::vector<std::vector<bool>>& flagged ,int numCol,int numRow,int numMine,int uiOffset){
    sf::Sprite sprite;
    sf::RectangleShape tile(sf::Vector2f(static_cast<float>(tileSize - 2), static_cast<float>(tileSize - 2))); // float キャストを追加

    if(currentState==GameState::MainMenu){
        sprite.setTexture(textures["mine"]);
        sf::Vector2u textureSize = sprite.getTexture()->getSize(); // 元画像の大きさ（ピクセル）
        float scaleX = static_cast<float>(window.getSize().x) / textureSize.x;
        float scaleY = static_cast<float>(window.getSize().y) / textureSize.y;
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0.f,0.f);
        //window.draw(sprite);
    }

    if(currentState==GameState::Playing||currentState==GameState::Win||currentState==GameState::GameOver){
        for (int i = 0; i < numCol; i++){
            for (int j = 0; j < numRow; j++){
                tile.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
            
                if(opened[i][j]){
                    tile.setFillColor(sf::Color::White);//開いたマスは白
                }else{
                    tile.setFillColor(sf::Color(200, 200, 200));//開いて無いマスの色
                }
                window.draw(tile);
                //数字のフォント
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(field.getCount(i, j)));
                text.setCharacterSize(24);
                // 数字の色の設定
                if(field.getCount(i, j) == 1){
                    text.setFillColor(sf::Color::Blue);
                }
                else if(field.getCount(i, j) == 2){
                    text.setFillColor(sf::Color::Green);
                }
                else if(field.getCount(i, j) >= 3){
                    text.setFillColor(sf::Color::Red);
                }
                sf::FloatRect textBounds = text.getLocalBounds();
                text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                text.setPosition(static_cast<float>(j * tileSize + tileSize / 2.0f), static_cast<float>(i * tileSize + tileSize / 2.0f + uiOffset));
                    //ここでwindow.draw(text)までやると未開放のマスに0が表示されてしまう
                if(currentState == GameState::GameOver){
                    if(field.Mined(i, j)){
                        sprite.setTexture(textures["mine"]);
                        sprite.setScale(static_cast<float>(tileSize) / textures["mine"].getSize().x,static_cast<float>(tileSize) / textures["mine"].getSize().y);
                        sprite.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
                        window.draw(sprite);
                    }else if(opened[i][j] && field.getCount(i,j) > 0){
                        window.draw(text);
                    }else if(field.Mined(i, j) && !opened[i][j] && !flagged[i][j]){ //踏んでない地雷は地雷画像
                        sprite.setTexture(textures["mine"]);
                        sprite.setScale(static_cast<float>(tileSize) / textures["mine"].getSize().x,static_cast<float>(tileSize) / textures["mine"].getSize().y);
                        sprite.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
                        window.draw(sprite);
                    }
                    else if(flagged[i][j]){
                        sprite.setTexture(textures["flag"]);
                        sprite.setScale(static_cast<float>(tileSize) / textures["flag"].getSize().x,static_cast<float>(tileSize) / textures["flag"].getSize().y);
                        sprite.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
                        window.draw(sprite);
                    }

                }else if(currentState == GameState::Win){
                    if (!field.Mined(i, j)){
                        int count = field.getCount(i, j);
                        if (count > 0) { // 数字が1以上の場合は数字を表示
                            /*sf::FloatRect textBounds = text.getLocalBounds();
                            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                            text.setPosition(static_cast<float>(j * tileSize + tileSize / 2.0f), static_cast<float>(i * tileSize + tileSize / 2.0f + uiOffset));*/
                            window.draw(text);
                        }
                    }else{
                        sprite.setTexture(textures["mine"]); 
                        sprite.setScale(static_cast<float>(tileSize) / textures["mine"].getSize().x,static_cast<float>(tileSize) / textures["mine"].getSize().y);
                        sprite.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
                        window.draw(sprite);
                    }
                }else{ //Playingのとき
                    if(flagged[i][j]){ // フラグ表示
                        sprite.setTexture(textures["flag"]);
                        sprite.setScale(static_cast<float>(tileSize) / textures["flag"].getSize().x,static_cast<float>(tileSize) / textures["flag"].getSize().y);
                        sprite.setPosition(static_cast<float>(j * tileSize), static_cast<float>(i * tileSize + uiOffset));
                        window.draw(sprite);
                    }else if(opened[i][j]){ 
                        int count = field.getCount(i, j);
                        if(count > 0){ // 周囲の地雷数が1以上の場合は数字を表示
                            window.draw(text);
                        }
                    }
                }
            }
        }
    }
}