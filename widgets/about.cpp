#include "about.h"

#include <QCoreApplication>
#include <QString>

#include "revision_utils.hpp"

#include "ui_about.h"

CAboutDlg::CAboutDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CAboutDlg)
{
  ui->setupUi(this);

  ui->labelTxt->setText ("<h2>" + QString {"WSJT-X v"
                                             + QCoreApplication::applicationVersion ()
                                             + " " + revision ()}.simplified () + "</h2>"
    "<h3> In memory of G4WJS, Bill Somerville (1956-2021),<br />"
    "who gave so much of himself to the WSJT project. </h3>"

    "WSJT-X implements a number of digital modes designed for <br />"
    "weak-signal Amateur Radio communication.  <br /><br />"
    "&copy; 2001-2024 by Joe Taylor, K1JT, Bill Somerville, G4WJS, <br />"
    "Steve Franke, K9AN, Nico Palermo, IV3NWV, <br />"
    "Uwe Risse, DG2YCB, and Brian Moran, N9ADG <br /><br />"
    "We gratefully acknowledge contributions from AC6SL, AE4JY,<br />"
    "DF2ET, DJ0OT, G3WDG, G4KLA, IW3RAB, K3WYC, KA1GT,<br />"
    "KA6MAL, KA9Q, KB1ZMX, KD6EKQ, KG4IYS, KI7MT, KK1D, ND0B,<br />"
    " PY2SDR, VE1SKY, VK3ACF, VK4BDJ, VK7MO, W3DJS, W3SZ, W4TI,<br />"
    " W4TV, and W9MDB.<br /><br />"
    "WSJT-X is licensed under the terms of Version 3 <br />"
    "of the GNU General Public License (GPL) <br /><br />"

    // GPLv3 §5(a): a modified version has to say that it was modified, and by
    // whom. It is also the honest thing to put in front of anyone about to
    // report a bug — the country filter and the uahamaward.com connection are
    // neither the WSJT-X team's work nor the WSJT-Z project's, and should not
    // become their correspondence.
    "<b>Modified build by Petro Ostapuk, UR3PKI.</b><br />"
    "This is not an official WSJT-Z release.<br />"
    "It adds a DXCC country filter for the decode windows and a<br />"
    "direct connection to uahamaward.com for logged contacts.<br />"
    "Report problems with those to the fork, not to the WSJT-Z<br />"
    "or WSJT-X teams:<br />"
    "<a href=\"https://github.com/uaro-radio/wsjt-z\">"
    "https://github.com/uaro-radio/wsjt-z</a><br /><br />"

    "<a href=" TO_STRING__ (PROJECT_HOMEPAGE) ">"
    "<img src=\":/icon_128x128.png\" /></a>"
    "<a href=\"https://www.gnu.org/licenses/gpl-3.0.txt\">"
    "<img src=\":/gpl-v3-logo.svg\" height=\"80\" /><br />"
    "https://www.gnu.org/licenses/gpl-3.0.txt</a>");
}

CAboutDlg::~CAboutDlg()
{
}
