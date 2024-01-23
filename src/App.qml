// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.15
import TestingExample 1.0

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "TestingExample"

    Screen01 {
        id: mainScreen
    }

}

