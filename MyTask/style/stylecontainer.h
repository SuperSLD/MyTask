#ifndef STYLECONTAINER_H
#define STYLECONTAINER_H

#include <QColor>
#include <QString>

namespace styles{
    /** объявления цветов */
    static const QString COLOR_BACKGROUND = "#FFFFFF";
    static const QString COLOR_TEXT_PRIMARY = "#242424";
    static const QString COLOR_TEXT_HINT= "#A6A6A6";
    static const QString COLOR_PRIMARY = "#4881B7";
    static const QString COLOR_BORDER = "#E6EBF0";
    static const QString COLOR_TEXT_RED = "#FF6262";
    static const QString COLOR_BUTTON_PRESSED = "#2A669C";

    static const QColor QT_COLOR_PRIMARY = QColor(72, 129, 183);

    /** объявления стилей */
    static const QString GLOBAL_BACK_WHITE =
            "QWidget#container {"
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
            "QFrame#fragment {"
            "background-color:"+COLOR_BACKGROUND+";"
                                                 "}";

    static const QString DESK_WIDGET =
            "QFrame#desk {"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "font-size:16px;"
            "padding: 0px;"
            "border-radius:8px;"
            "}";

    static const QString SCROL_BAR =
            "QScrollBar:vertical {"
            "   border: 0px solid "+COLOR_BORDER+";"
            "   background: "+COLOR_BORDER+";"
            "   width: 4px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar:horizontal {"
            "   border: 0px solid "+COLOR_BORDER+";"
            "   background: "+COLOR_BORDER+";"
            "   height: 0px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle {"
            "   background: "+COLOR_BORDER+";"
            "   border: 3px solid "+COLOR_BORDER+";"
            "   border-radius: 6px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "   height: 0px;"
            "   subcontrol-position: bottom;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical {"
            "   height: 0 px;"
            "   subcontrol-position: top;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:horizontal {"
            "   width: 0px;"
            "   subcontrol-position: right;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:horizontal {"
            "   width: 0 px;"
            "   subcontrol-position: left;"
            "   subcontrol-origin: margin;"
            "}";

    static const QString TEXT_DARK_LABLE =
            "color:" + COLOR_TEXT_PRIMARY + ";"
            "font-size:16px;";

    static const QString TEXT_HINT_SMAL_LABLE =
            "color:" + COLOR_TEXT_HINT + ";"
            "font-size:14px;";

    static const QString TEXT_PRIMARY_SMAL_LABLE =
            "color:" + COLOR_PRIMARY + ";"
            "font-size:14px;";

    static const QString TEXT_PIMARY_18PX_LABLE =
            "color:" + COLOR_PRIMARY + ";"
            "font-size:18px;";

    static const QString TEXT_HINT_LABLE =
            "color:" + COLOR_TEXT_HINT+ ";"
            "font-size:16px;";

    static const QString TEXT_HINT_16PX_LABLE =
            "color:" + COLOR_TEXT_HINT + ";"
            "font-size:16px;";

    static const QString TEXT_HINT_18PX_LABLE =
            "color:" + COLOR_TEXT_HINT + ";"
            "font-size:18px;";

    static const QString TEXT_PRIMARY_16PX_LABLE =
            "color:" + COLOR_PRIMARY + ";"
            "font-size:16px;";

    static const QString TEXT_DARK_18PX_LABLE =
            "color:" + COLOR_TEXT_PRIMARY + ";"
            "font-size:18px;";

};


class StyleContainer
{
public:
    StyleContainer();
};

#endif // STYLECONTAINER_H
