#include "gui.hpp"

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

    handleCallbacks();
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

void GUI::handleCallbacks()
{
    settingsBtn->onPress([this] {
        settingsWindow->setVisible(!settingsWindow->isVisible());
    });

    fpsCheckbox->onChange([this] {
        fpsLabel->setVisible(fpsCheckbox->isChecked());
    });
}
