#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/audio.hpp"

sf::Font setfont(const std::string& path);
sf::Texture loadTexture(const std::string& path);
sf::Sprite createsprite(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY);
sf::Text settext(const sf::Font& font, float CharSize, float posX, float posY, float FCa, float FCb, float FCc);
void updateUpcomingSongs(int currentIndex, const std::vector<std::string>& songTitles, std::vector<sf::Text>& upcomingTextList, sf::Font& font, sf::Vector2f startPos);
sf::RectangleShape createrectangle(float sizex, float sizey, float posX, float posY, float FCa, float FCb, float FCc);
sf::CircleShape createcircle(float radius, float posX, float posY, float originx, float originy, float OT);
sf::RenderWindow window(sf::VideoMode(1280, 720), "MY GAME");
int currentSongIndex = 0;
//fonts
sf::Font font1 = setfont("backso.ttf");
sf::Font font2 = setfont("rycon.ttf");
//setting background
sf::Texture backgroundtexture2 = loadTexture("Bg 4.png");
sf::Texture backgroundtexture1 = loadTexture("bg1.png");
sf::Sprite backgroundsprite;
//border
sf::Texture bordertexture = loadTexture("border.png");
sf::Sprite border1 = createsprite(bordertexture, 20, 5, 0.5f, 0.5f);
sf::Sprite border2 = createsprite(bordertexture, 960, 5, 0.5f, 0.5f);
// play pause 
sf::CircleShape circle = createcircle(30.0f, 500, 600, 0, 0, 4);                            //button circle
sf::Texture playtexture = loadTexture("play 3.png");       //play pause icons
sf::Texture pausetexture = loadTexture("pause 2.png");
sf::Sprite icon = createsprite(playtexture, 513, 611, 0.175f, 0.175f);
sf::Sprite icon2 = createsprite(pausetexture, 497, 597, 0.13f, 0.13f);
sf::Text play = settext(font2, 33, 580, 605, 255, 255, 255);        //play pause text
//music controls
sf::Texture nexttexture = loadTexture("next.png");
sf::Sprite next = createsprite(nexttexture, 765, 610, 0.170f, 0.170f);
sf::Texture prevtexture = loadTexture("prev.png");
sf::Sprite prev = createsprite(prevtexture, 425, 610, 0.170f, 0.170f);
//disc
sf::Texture disctexture = loadTexture("disx.png");
sf::Sprite disc = createsprite(disctexture, 300, 300, 0.7f, 0.7f);
//star
sf::Texture startexture = loadTexture("stars.png");
sf::Sprite starleft = createsprite(startexture, 140, 587, 0.9f, 0.9f);
sf::Sprite starright = createsprite(startexture, 840, 587, 0.9f, 0.9f);
//minion1
sf::Texture min1texture = loadTexture("minion 1.png");
sf::Sprite min1sprite = createsprite(min1texture, 400, 200, 0.7f, 0.9f);
//minion 1 mouth
sf::Texture min1mouthTexture = loadTexture("minion m.png");
sf::Sprite min1mouthsprite = createsprite(min1mouthTexture, 490, 320, 0.1f, 0.1f);
//minion 2
sf::Texture min2texture = loadTexture("minion 2.png");
sf::Sprite min2sprite = createsprite(min2texture, 560, 270, 0.2f, 0.2f);
//minion 2 mouth
sf::Texture min2mouthTexture = loadTexture("minion m.png");
sf::Sprite min2mouthsprite = createsprite(min2mouthTexture, 645, 390, 00.1f, 0.1f);
//other min
sf::Texture min3Texture = loadTexture("min3.png");
sf::Sprite min3sprite = createsprite(min3Texture, 10, 60, 1.0f, 1.0f);
sf::Texture min4Texture = loadTexture("min left.png");
sf::Sprite min4sprite = createsprite(min4Texture, 0, 180, 1.0f, 1.0f);
sf::Texture min5Texture = loadTexture("min right.png");
sf::Sprite min5sprite = createsprite(min5Texture, 1020, 0, 0.8f, 0.8f);
//banana sound
sf::Music banana;
bool miniongame = false;
//minion 2 sound
sf::Music min2sound;
//Game Name             
sf::Text gametitle = settext(font2, 50, 365, 10, 255, 255, 255);
//music
sf::Music music;
//mouth movements
    //volume
float initialMouseY = 0;
bool isDragging = false;
sf::Vector2f dragOffset;
//play
bool ispressed = false;
bool musicplayer = true;
//theme changer
bool ispressed2 = false;
sf::Texture themeicontexture = loadTexture("switch.png");
sf::Sprite themeicon = createsprite(themeicontexture, 1195, 635, 0.25f, 0.25f);
//music bar
sf::RectangleShape progressBarBack = createrectangle(1000, 10, 140, 560, 100, 100, 100);
sf::RectangleShape progressBar = createrectangle(0, 10, 140, 560, 255, 255, 255);
std::vector<std::string> songTitles = {
        "Pal-Pal",
    "CREAM POSSE",
    "Tere Naal",
    "Gorgeous",
    "Diet Mountain Dew",
    "BIRDS OF A FEATHER",
    "Haal",
    "HIGH ON YOU",
    "Cinnamon Girl",
    "Ocean Eyes",
    "Taare Gin Gin",
    "Humraah"
};
//audio name
sf::Text audioname = settext(font2, 24, 200, 480, 255, 255, 255);
// Vertical pitch Track
sf::RectangleShape pitchTrack = createrectangle(5, 250, 700, 200, 255, 255, 255);
// pitch Handle
sf::CircleShape pitchHandle = createcircle(10, 702, 200 + 168, 10, 10, 8);;
bool ispitchDragging = false;
//pitch icon
sf::Texture pitchtexture = loadTexture("pitch.png");
sf::Sprite pitch = createsprite(pitchtexture, 680, 465, 0.2f, 0.2f);
// Vertical Volume Track
sf::RectangleShape volumeTrack = createrectangle(5, 250, 600, 200, 255, 255, 255);
// Volume Handle
sf::CircleShape volumeHandle = createcircle(10, 602, 200 + 220, 10, 10, 8);
bool isVolumeDragging = false;
//volume icon
sf::Texture volumetexture = loadTexture("volume1.png");
sf::Sprite volume = createsprite(volumetexture, 585, 465, 0.2f, 0.2f);
std::vector<sf::Text> upcomingTextList;

sf::Texture loadTexture(const std::string& path) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)){}
    texture.setSmooth(true);
    return texture;
}
sf::Sprite createsprite(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
    return sprite;
}
sf::Font setfont(const std::string& path) {
    sf::Font font;
    if (!font.loadFromFile(path)) {};
    return font;
}
sf::Text settext(const sf::Font& font,float CharSize,float posX, float posY,float FCa,float FCb, float FCc) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(CharSize);
    text.setPosition(posX, posY);
    text.setFillColor(sf::Color(FCa, FCb, FCc));
    return text;
}
std::vector<std::string> songList = {
    "Pal-Pal.ogg",
    "CREAM POSSE.wav",
    "Tere Naal.wav",
    "Gorgeous.wav",
    "Diet Mountain Dew.wav",
    "BIRDS OF A FEATHER.wav",
    "Haal.wav",
    "HIGH ON YOU.wav",
    "Cinnamon Girl.wav",
    "Ocean Eyes.wav",
    "Taare Gin Gin.wav",
    "humraah.ogg"
};
void updateUpcomingSongs(int currentIndex, const std::vector<std::string>& songTitles, std::vector<sf::Text>& upcomingTextList, sf::Font& font, sf::Vector2f startPos) {
    upcomingTextList.clear();
    int maxUpcoming = 11; 
    for (int i = 1; i <= maxUpcoming; ++i) {
        int nextIndex = (currentIndex + i) % songTitles.size();
        sf::Text songText;
        songText.setFont(font);
        songText.setCharacterSize(24);
        songText.setFillColor(sf::Color::White);
        songText.setString(" - " + songTitles[nextIndex]);
        songText.setPosition(startPos.x, startPos.y + (i - 1) * 25); // stagger vertically
        upcomingTextList.push_back(songText);
    }
}
sf::RectangleShape createrectangle(float sizex,float sizey, float posX, float posY, float FCa, float FCb, float FCc){
    sf::RectangleShape progressBarBack;
    progressBarBack.setSize(sf::Vector2f(sizex, sizey));
    progressBarBack.setFillColor(sf::Color(FCa,FCb, FCc));
    progressBarBack.setPosition(posX, posY);  // Position it nicely
    return progressBarBack;
}
sf::CircleShape createcircle(float radius, float posX, float posY,float originx,float originy,float OT) {
    sf::CircleShape volumeHandle;
    volumeHandle.setRadius(radius);
    volumeHandle.setFillColor(sf::Color::White);
    volumeHandle.setOrigin(originx,originy);
    volumeHandle.setPosition(posX, posY);
    volumeHandle.setOutlineColor(sf::Color::Black);
    volumeHandle.setOutlineThickness(OT);
    return volumeHandle;
}
void handledragging(sf::RenderWindow& window, sf::Event& event, const sf::CircleShape& pitchHandle, bool& isDragging, bool musicplayeractive) {
    if (!musicplayeractive) return;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (pitchHandle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            isDragging = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }
}
void handlevoldragmovement(sf::RenderWindow&window ,sf::Event&event,bool&isVolumeDragging,sf::RectangleShape& volumeTrack,sf::CircleShape&volumeHandle,sf::Music &music) {
    // Handle dragging movement
    if (event.type == sf::Event::MouseMoved && isVolumeDragging) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        float yMin = volumeTrack.getPosition().y;
        float yMax = yMin + volumeTrack.getSize().y;
        float clampedY = std::max(yMin, std::min(mousePos.y, yMax));
        volumeHandle.setPosition(volumeHandle.getPosition().x, clampedY);
        // Volume (inverse: top = 100, bottom = 0)
        float volume = (1.0f - ((clampedY - yMin) / volumeTrack.getSize().y)) * 100.f;
        music.setVolume(volume);
    }
}
void handlepitchdragmovement(sf::RenderWindow& window, sf::Event& event, bool&ispitchDragging, sf::RectangleShape& pitchTrack, sf::CircleShape& pitchHandle, sf::Music& music) {
    if (event.type == sf::Event::MouseMoved && ispitchDragging) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        float yMin = pitchTrack.getPosition().y;
        float yMax = yMin + pitchTrack.getSize().y;
        float clampedY = std::max(yMin, std::min(mousePos.y, yMax));
        pitchHandle.setPosition(pitchHandle.getPosition().x, clampedY);
        // Map Y to pitch (inverted: top = 2.0x, bottom = 0.5x)
        float percent = 1.0f - ((clampedY - yMin) / pitchTrack.getSize().y);
        float pitch = 0.5f + percent * 1.5f;  // range 0.5 to 2.0
        music.setPitch(pitch);
    }
}
void minmouthdragstart(sf::RenderWindow& window, sf::Event&event,sf::Sprite &min1mouthsprite,bool &isDragging,sf::Vector2f&dragOffset,float&initialMouseY) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (min1mouthsprite.getGlobalBounds().contains(mousePos)) {
            isDragging = true;
            dragOffset = mousePos - min1mouthsprite.getPosition();
            initialMouseY = mousePos.y; // store starting Y
        }
    }
}
void minmouthdragend(sf::Event& event,bool&isDragging) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }
}
void minmouthdrag(sf::RenderWindow&window, sf::Event&event,sf::Sprite& min1mouthsprite,sf::Sprite &min2mouthsprite,bool&isDragging,float&initialMouseY,sf::Music &music, sf::Music& banana, sf::Music& min2sound) {
    if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        float diff = mousePos.y - initialMouseY;
        float baseHeight = 100.f;
        float currentBaseYScale = 0.1f;
        float stretchAmount = currentBaseYScale + (diff / baseHeight) * 0.2f; // vertical stretch
        if (stretchAmount < 0.05f) stretchAmount = 0.05f;
        if (stretchAmount > 0.24f) stretchAmount = 0.24f;
        float stretch2Amount = stretchAmount;
        if (stretch2Amount < 0.05f) stretch2Amount = 0.05f;
        if (stretch2Amount > 0.17f) stretch2Amount = 0.17f;
        min1mouthsprite.setScale(0.1f, stretchAmount);
        min2mouthsprite.setScale(0.1f, stretch2Amount);
        float volume = ((stretchAmount - 0.05f) / (0.24f - 0.05f)) * 100.f;
        music.setVolume(volume);
        banana.setVolume(volume);
        min2sound.setVolume(volume);
    }
}
void renderif(sf::RenderWindow& window, sf::Sprite& disc, sf::Text& gametitle,sf::Music &music
    ,sf::RectangleShape& progressBar,bool& ispressed,sf::Sprite& icon2,sf::Sprite& border2
    , sf::Sprite &icon, sf::Text& play, std::vector<sf::Text>& upcomingTextList
    ,sf::Sprite &border1, sf::Sprite& next, sf::Sprite&prev, sf::RectangleShape& progressBarBack
    ,sf::Text& audioname, sf::RectangleShape& volumeTrack, sf::CircleShape& volumeHandle, 
    sf::RectangleShape& pitchTrack, sf::CircleShape& pitchHandle, sf::Sprite &starleft,
    sf::Sprite& starright, sf::Sprite& volume, sf::Sprite& pitch, const std::vector<std::string>& songTitles,int& currentSongIndex) {
    window.draw(disc); window.draw(gametitle);
    if (music.getStatus() == sf::SoundSource::Playing || music.getStatus() == sf::SoundSource::Paused) {
        sf::Time current = music.getPlayingOffset();
        sf::Time total = music.getDuration();
        if (total.asSeconds() > 0) {
            float progress = current.asSeconds() / total.asSeconds();
            progressBar.setSize(sf::Vector2f(1000 * progress, 10)); // 1000 is the full width
        }
    }
    audioname.setString(songTitles[currentSongIndex]);
    if (ispressed) {
        window.draw(icon2);
        play.setString("Pause");
        window.draw(play);
    }
    else {
        window.draw(icon);
        play.setString("Play");
        window.draw(play);
    }
    for (int i = 0; i < upcomingTextList.size(); ++i) {
        window.draw(upcomingTextList[i]);
    }
    window.draw(border1);window.draw(border2);window.draw(next);window.draw(prev);window.draw(progressBarBack); window.draw(progressBar);
    window.draw(audioname);window.draw(volumeTrack);window.draw(volumeHandle);window.draw(pitchTrack);window.draw(pitchHandle);
    window.draw(starleft);window.draw(starright);window.draw(volume);window.draw(pitch);
}
void renderelse(sf::RenderWindow&window, sf::Text& gametitle,sf::Sprite& min3sprite, sf::Sprite& min1sprite,
    sf::Sprite& min1mouthsprite, sf::Sprite& min2sprite, sf::Sprite& min2mouthsprite, sf::Sprite& min4sprite,
    sf::Sprite& min5sprite, sf::CircleShape& circle,bool& ispressed, sf::Sprite& icon2, sf::Text& play, sf::Sprite& icon) {
    window.draw(min3sprite);window.draw(gametitle);window.draw(min1sprite);window.draw(min1mouthsprite);window.draw(min2sprite);
    window.draw(min2mouthsprite);window.draw(min4sprite);window.draw(min5sprite); window.draw(circle);
    min1mouthsprite.setOrigin(min1mouthTexture.getSize().x / 2.f, 0);
    min2mouthsprite.setOrigin(min2mouthTexture.getSize().x / 2.0f, 0);
    if (ispressed) {
        window.draw(icon2);
        play.setString("Pause");
        window.draw(play);
    }
    else {
        window.draw(icon);
        play.setString("Play");
        window.draw(play);
    }
}
void render(sf::RenderWindow& window, sf::Sprite& disc, sf::Text& gametitle, sf::Music& music
    , sf::RectangleShape& progressBar, bool& ispressed, sf::Sprite& icon2, sf::Sprite& border2
    , sf::Sprite& icon, sf::Text& play, std::vector<sf::Text>& upcomingTextList
    , sf::Sprite& border1, sf::Sprite& next, sf::Sprite& prev, sf::RectangleShape& progressBarBack
    , sf::Text& audioname, sf::RectangleShape& volumeTrack, sf::CircleShape& volumeHandle,
    sf::RectangleShape& pitchTrack, sf::CircleShape& pitchHandle, sf::Sprite& starleft,
    sf::Sprite& starright, sf::Sprite& volume, sf::Sprite& pitch, sf::Sprite& min3sprite, sf::Sprite& min1sprite,
    sf::Sprite& min1mouthsprite, sf::Sprite& min2sprite, sf::Sprite& min2mouthsprite, sf::Sprite& min4sprite,
    sf::Sprite& min5sprite, sf::CircleShape& circle, sf::Sprite& backgroundsprite, sf::Sprite& themeicon,
    bool& ispressed2, sf::Texture& backgroundtexture2, sf::Texture& backgroundtexture1,sf::Texture& disctexture) {
    window.setFramerateLimit(60);
    window.clear();
    if (!ispressed2){
        backgroundsprite.setTexture(backgroundtexture2);
        disc.setOrigin(
            disctexture.getSize().x / 2.0f,
            disctexture.getSize().y / 2.0f);
        gametitle.setString("Music Player");
        gametitle.setFillColor(sf::Color::White);
        gametitle.setOutlineThickness(0);
        updateUpcomingSongs(currentSongIndex, songTitles, upcomingTextList, font2, sf::Vector2f(780, 180));
    }
    window.draw(backgroundsprite);
    window.draw(themeicon);
    if (!ispressed2) {
        renderif(window, disc, gametitle, music, progressBar, ispressed, icon2, border2, icon, play,
            upcomingTextList, border1, next, prev, progressBarBack, audioname,
            volumeTrack, volumeHandle, pitchTrack, pitchHandle, starleft, starright, volume, pitch, songTitles,currentSongIndex);
    }
    else {
        renderelse(window, gametitle, min3sprite, min1sprite, min1mouthsprite, min2sprite, min2mouthsprite, min4sprite, min5sprite, circle, ispressed, icon2, play, icon);
    }
    window.display();
}
void loadSong(sf::Music& music, const std::vector<std::string>& songList, int index) {
    if (!music.openFromFile(songList[index])) {}
    music.setLoop(true);
    music.play();
}
void themechanger(sf::RenderWindow& window, sf::Event& event, sf::Sprite&themeicon, bool& ispressed2, sf::Sprite& backgroundsprite,
    sf::Texture&backgroundtexture1,sf::Text&gametitle,sf::Font &font1,sf::Text&play,sf::Music&music,bool&miniongame,bool&musicplayer, 
    sf::Texture& backgroundtexture2, sf::Font& font2, int& currentSongIndex, std::vector<std::string>& songTitles, std::vector<sf::Text>& upcomingTextList,
    sf::CircleShape &circle,sf::Sprite&min2mouthsprite,sf::Texture& min2mouthTexture,sf::Music&banana ,sf::Music& min2sound) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (themeicon.getGlobalBounds().contains(mousePos))
        {
            ispressed2 = !ispressed2;
            if (ispressed2) {
                backgroundsprite.setTexture(backgroundtexture1, true);
                backgroundsprite.setScale(
                    window.getSize().x / (float)backgroundtexture1.getSize().x,
                    window.getSize().y / (float)backgroundtexture1.getSize().y);
                gametitle.setString("<Minion Game>");
                gametitle.setFont(font1);
                gametitle.setFillColor(sf::Color(0, 81, 156));
                gametitle.setOutlineColor(sf::Color::White);
                gametitle.setOutlineThickness(4);
                gametitle.setPosition(10, 10);
                play.setFont(font1);
                play.setFillColor(sf::Color(0, 81, 156));
                play.setOutlineColor(sf::Color::White);
                play.setOutlineThickness(4);
                play.setPosition(580, 611);
                circle.setFillColor(sf::Color(0, 81, 156));
                circle.setOutlineColor(sf::Color::White);
                music.stop();
                miniongame = true;
                musicplayer = false;
                if (!banana.openFromFile("banana.wav")) {}
                banana.setLoop(false);
                if (!min2sound.openFromFile("minion 2 sound.wav")) {}
                min2sound.setLoop(false);
            }
            else {
                backgroundsprite.setTexture(backgroundtexture2, true);
                backgroundsprite.setScale(
                    window.getSize().x / (float)backgroundtexture2.getSize().x,
                    window.getSize().y / (float)backgroundtexture2.getSize().y);
                gametitle.setString("Music Player");
                gametitle.setFillColor(sf::Color::White);
                gametitle.setFont(font2);
                gametitle.setOutlineThickness(0);
                gametitle.setPosition(365, 10);
                play.setFont(font2);
                play.setOutlineThickness(0);
                play.setFillColor(sf::Color::White);
                play.setPosition(580, 605);
                miniongame = false;
                musicplayer = true;
                updateUpcomingSongs(currentSongIndex, songTitles, upcomingTextList, font2, sf::Vector2f(780, 180));
            }
        }
    }
}
void playpause(sf::Event& event, sf::RenderWindow& window, int& currentSongIndex, std::vector<std::string>& songTitles,sf::CircleShape&circle
    ,bool&ispressed,bool&ispressed2,sf::Music&music,sf::Text&audioname,sf::Sprite& min1mouthsprite, sf::Sprite& min2mouthsprite, bool& isDragging, 
    sf::Vector2f& dragOffset,float& initialMouseY,
    sf::Music& banana,sf::Music&  min2sound) {

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (circle.getGlobalBounds().contains(mousePos)) {
            if (!ispressed) {
                ispressed = true;
                if (ispressed2) {  // Minion Game mode
                    if (music.getStatus() != sf::SoundSource::Playing) {
                        music.stop();
                        if (music.openFromFile("bgsound.ogg")) {
                            music.setLoop(true);
                            music.play();
                        }
                    }
                    else {
                        music.play(); // Resume if already paused
                    }
                }
                else { // Music Player mode
                    if (music.getStatus() != sf::SoundSource::Playing) {
                        loadSong(music, songList, currentSongIndex);
                    }
                    else {
                        music.play();
                    }
                    audioname.setString(songTitles[currentSongIndex]);
                }
            }
            else {
                ispressed = false;
                music.pause();
            }
        }
    }
    if (ispressed2) {
        minmouthdragstart(window, event, min1mouthsprite, isDragging, dragOffset, initialMouseY);
        minmouthdragend(event, isDragging);
        minmouthdrag(window, event, min1mouthsprite, min2mouthsprite, isDragging, initialMouseY, music, banana, min2sound);
    }
}
void minionssound(sf::RenderWindow&window,sf::Event &event,sf::Sprite &min1sprite,sf::Music&banana,bool& miniongame,sf::Sprite& min1mouthsprite) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (min1sprite.getGlobalBounds().contains(mousePos) && miniongame == true && !min1mouthsprite.getGlobalBounds().contains(mousePos)) {
            if (banana.getStatus() == sf::Sound::Playing) {
                banana.stop();
            }
            else {
                banana.play();
                banana.setPlayingOffset(sf::Time::Zero);
            }
        }
    }
}
void musicchange(sf::RenderWindow& window, sf::Event& event, sf::Sprite& next, bool& musicplayer, int& currentSongIndex, sf::Music& music, sf::Text& audioname, \
    std::vector<std::string> &songTitles, std::vector<sf::Text>&upcomingTextList,sf::Font&font2,sf::Sprite&prev) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        // Handle next song
        if (next.getGlobalBounds().contains(mousePos) && musicplayer == true) {
            currentSongIndex++;
            if (currentSongIndex >= songList.size())
                currentSongIndex = 0; // Loop back to the first song
            loadSong(music, songList, currentSongIndex);
            audioname.setString(songTitles[currentSongIndex]);
            updateUpcomingSongs(currentSongIndex, songTitles, upcomingTextList, font2, sf::Vector2f(780, 180));
        }
        // Handle previous song
        if (prev.getGlobalBounds().contains(mousePos) && musicplayer == true) {
            if (currentSongIndex == 0)
                currentSongIndex = songList.size() - 1; // Loop to the last song
            else
                currentSongIndex--;
            loadSong(music, songList, currentSongIndex);
            audioname.setString(songTitles[currentSongIndex]);
            updateUpcomingSongs(currentSongIndex, songTitles, upcomingTextList, font2, sf::Vector2f(780, 180));
        }
    }
}
int main() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            //pitch
            handledragging(window, event, pitchHandle, ispitchDragging, musicplayer);
            handlepitchdragmovement(window, event, ispitchDragging, pitchTrack, pitchHandle, music);
            //volume
            handledragging(window, event, volumeHandle, isVolumeDragging, musicplayer);
            handlevoldragmovement(window, event, isVolumeDragging, volumeTrack, volumeHandle, music);
            //banana sound
            minionssound(window,event, min1sprite, banana, miniongame, min1mouthsprite);
            //minion 2 sound
            minionssound(window,event,min2sprite,min2sound,miniongame,min2mouthsprite );
            //next/prev
            musicchange(window, event, next, musicplayer, currentSongIndex, music, audioname, songTitles, upcomingTextList, font2, prev);
            //theme changer
            themechanger(window, event, themeicon, ispressed2, backgroundsprite, backgroundtexture1, gametitle, font1, play, music, miniongame, musicplayer, backgroundtexture2,
                font2, currentSongIndex, songTitles, upcomingTextList,circle,min2mouthsprite,min2mouthTexture,banana,min2sound);
            //play/pause
            playpause(event, window, currentSongIndex, songTitles, circle, ispressed, ispressed2, music, audioname, min1mouthsprite, min2mouthsprite, isDragging, dragOffset,
                initialMouseY, banana, min2sound);
        }disc.rotate(1.0f);
        //render
            render(window, disc, gametitle,music, progressBar, ispressed,  icon2, border2, icon, play,
                upcomingTextList, border1, next, prev, progressBarBack, audioname,
                volumeTrack, volumeHandle, pitchTrack,pitchHandle, starleft, starright, volume, pitch, min3sprite,
                min1sprite, min1mouthsprite, min2sprite, min2mouthsprite, min4sprite,
                min5sprite, circle, backgroundsprite, themeicon, ispressed2,backgroundtexture2,backgroundtexture1,disctexture);
    }
    return 0;
}
 