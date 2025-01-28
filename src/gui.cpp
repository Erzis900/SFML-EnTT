#include "gui.hpp"
#include <iostream>

GUI::GUI(sf::RenderWindow &window) : gui(window)
{
    gui.loadWidgetsFromFile("../../forms/gameForm.txt");

    settingsWindow = gui.get<tgui::ChildWindow>("settingsWindow");
    settingsBtn = gui.get<tgui::Button>("settingsBtn");
    fpsCheckbox = gui.get<tgui::CheckBox>("fpsCheckbox");
    fpsLimitCombo = gui.get<tgui::ComboBox>("fpsLimitCombo");
    resolutionCombo = gui.get<tgui::ComboBox>("resolutionCombo");
    fpsLabel = gui.get<tgui::Label>("fpsLabel");

    fpsLabel->setVisible(fpsCheckbox->isChecked());

    handleCallbacks(window);
}

void GUI::handleEvent(sf::Event event)
{
    gui.handleEvent(event);
}

void GUI::draw()
{
    gui.draw();
}

void GUI::update(int fps)
{
    if (fpsCheckbox->isChecked()) {
        fpsLabel->setText("FPS: " + std::to_string(static_cast<int>(fps)));
    }
}

void GUI::handleCallbacks(sf::RenderWindow &window)
{
    settingsBtn->onPress([this] {
        settingsWindow->setVisible(!settingsWindow->isVisible());
    });

    fpsCheckbox->onChange([this] {
        fpsLabel->setVisible(fpsCheckbox->isChecked());
    });

    fpsLimitCombo->onItemSelect([this, &window] {
        window.setFramerateLimit(fpsLimitCombo->getSelectedItem().toInt());
    });

    resolutionCombo->onItemSelect([this, &window] {
        std::stringstream ss(resolutionCombo->getSelectedItem().toStdString());
        int width, height;

        std::vector<std::string> tokens;
        std::string token;
        while(std::getline(ss, token, 'x'))
        {
            tokens.push_back(token);
        }

        window.setSize({static_cast<unsigned int>(std::stoi(tokens[0])), static_cast<unsigned int>(std::stoi(tokens[1]))});
    });
}
