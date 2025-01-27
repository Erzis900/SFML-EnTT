#pragma once
#include "pch.hpp"

class GUI 
{
public:
    GUI(sf::RenderWindow &window);
    void handleEvent(sf::Event event);
    void draw();

    void update(int fps);
private:
    tgui::Gui gui;
    tgui::ChildWindow::Ptr settingsWindow;
    tgui::Button::Ptr settingsBtn;
    tgui::CheckBox::Ptr fpsCheckbox;
    tgui::ComboBox::Ptr fpsLimitCombo;
    tgui::ComboBox::Ptr resolutionCombo;
    tgui::Label::Ptr fpsLabel;

    void handleCallbacks();
};