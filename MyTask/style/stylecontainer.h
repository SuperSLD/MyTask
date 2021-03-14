#ifndef STYLECONTAINER_H
#define STYLECONTAINER_H

#include <QString>


/**
 * @brief The StyleContainer class
 *
 * Хранилище цветов и стилей.
 * Это удобнее чем css файлы, потому
 * что они собираются черт знает как.
 *
 * Проще записать стили сюда чем
 * каждый раз выполнять clean build.
 */
namespace styles{
    /** объявления цветов */
    static const QString COLOR_BACKGROUND = "#FFFFFF";
    static const QString COLOR_TEXT_PRIMARY = "#242424";
    static const QString COLOR_TEXT_HINT= "#A6A6A6";
    static const QString COLOR_PRIMARY = "#4881B7";
    static const QString COLOR_BORDER = "#E6EBF0";
    static const QString COLOR_TEXT_RED = "#FF6262";
    static const QString COLOR_BUTTON_PRESSED = "#2A669C";

    /** объявления стилей */
    static const QString GLOBAL_BACK_WHITE =
            "QWidget {"
            "   background-color:"+COLOR_BACKGROUND+";"
            "}";

    static const QString FRAME_8PX_WHITE =
            "QFrame {"
            "   background-color:"+COLOR_BACKGROUND+";"
            "   border-radius:8px;"
            "   height:392px;"
            "   width:804px;"
            "}";

    static const QString SPLASH_ICON =
            "   height:274px;"
            "   width:325px;";

    static const QString START_ICON =
            "   height:300px;"
            "   width:300px;";

    static const QString TITLE_LABLE =
            "color:" + COLOR_TEXT_PRIMARY + ";"
            "font-size:24px;";
    static const QString HINT_LABLE =
            "color:" + COLOR_TEXT_HINT + ";"
            "font-size:14px;";

    static const QString BUTTON_SOLID =
            "QPushButton {"
            "color: "+COLOR_BACKGROUND+";"
            "background-color:"+COLOR_PRIMARY+";"
            "border:none;"
            "padding:8px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BUTTON_PRESSED+";"
            "}";

    static const QString BUTTON_DISABLED =
            "QPushButton {"
            "color: "+COLOR_TEXT_HINT+";"
            "background-color:"+COLOR_BORDER+";"
            "border:none;"
            "padding:8px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString BUTTON_EMPTY =
            "QPushButton {"
            "color: "+COLOR_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_PRIMARY+";"
            "padding:8px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString BUTTON_PROFILE =
            "QPushButton {"
            "color: "+COLOR_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "padding:8px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString BUTTON_PROFILE_RED =
            "QPushButton {"
            "color: "+COLOR_TEXT_RED+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "padding:8px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString EDIT_TEXT =
            "border: 1px solid "+COLOR_BORDER+";"
            "color: "+COLOR_TEXT_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "font-size:16px;"
            "border-radius:8px;"
            "padding:8px;";

    static const QString BACK_WHITE =
            "background-color:"+COLOR_BACKGROUND+";";
};


class StyleContainer
{
public:
    StyleContainer();
};

#endif // STYLECONTAINER_H
