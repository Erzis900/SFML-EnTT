#pragma once
#include "pch.hpp"
#include "config.hpp"

class GUI 
{
public:
    GUI(sf::RenderWindow &window, Config &config);
    void handleEvent(sf::Event event);
    void draw();

    void update(int fps);
private:
    tgui::Gui gui;
    tgui::ChildWindow::Ptr settingsWindow;
    tgui::Button::Ptr settingsBtn;

    tgui::Label::Ptr fpsLabel;

    tgui::CheckBox::Ptr fpsCheckbox;
    tgui::CheckBox::Ptr fullscreenCheckbox;

    tgui::ComboBox::Ptr fpsLimitCombo;
    tgui::ComboBox::Ptr resolutionCombo;

    void handleCallbacks(sf::RenderWindow &window);

    sf::Vector2u windowSize;
    unsigned int fpsLimit;
};