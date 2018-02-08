## QStyle-demo


This project provides a standalone version of the oxygen-demo5 utility from KDE's Oxygen widget style.
It is a look-and-feel explorer that sets up a window with a selection of representative widgets organised in pages.
A popup menu allows to select a widget style from those available, and a toggle switch to activate right-to-left mode.

The code has been modified to have as little dependencies as possible:

- Qt5 (only the QtBase module)
- cmake

Only 3 non-Qt widgets are exposed: KPageView, KTitleWidget and KActionMenu, from the KF5 KWidgetsAddons frameworks.
The sources for these widgets are included (from KF5 5.42.0).
