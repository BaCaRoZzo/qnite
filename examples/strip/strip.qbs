import qbs


Project {
    CppApplication {
        Depends { name: "qnite" }
        Depends { name: "Qt.quick" }

        files: [
            "strip.qrc",
            "main.cpp",
        ]
    }
}
