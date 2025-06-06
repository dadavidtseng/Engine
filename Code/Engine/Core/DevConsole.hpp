//----------------------------------------------------------------------------------------------------
// DevConsole.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include "Engine/Core/EventSystem.hpp"
#include "Engine/Core/Rgba8.hpp"

//----------------------------------------------------------------------------------------------------
#if defined ERROR
#undef ERROR
#endif

//----------------------------------------------------------------------------------------------------
class BitmapFont;
class Camera;
class Renderer;
class Timer;
struct AABB2;

//----------------------------------------------------------------------------------------------------
/// @brief
/// Stores the text and color for an individual line of text.
struct sDevConsoleLine
{
    Rgba8  m_color;
    String m_text;
    int    m_frameNumberPrinted;
    double m_timePrinted;
};

//----------------------------------------------------------------------------------------------------
enum eDevConsoleMode : int8_t
{
    OPEN_FULL,
    OPEN_PARTIAL,
    HIDDEN,
    COMMAND_LINE_PROMPT,
    NUM
};

//----------------------------------------------------------------------------------------------------
/// @brief
/// Configuration settings for the Developer Console.
/// A valid Renderer and Camera must be assigned for the console to function properly.
struct sDevConsoleConfig
{
    Renderer* m_defaultRenderer   = nullptr;
    Camera*   m_defaultCamera     = nullptr;
    String    m_defaultFontName   = "SquirrelFixedFont";
    float     m_defaultFontAspect = 1.f;
    float     m_maxLinesDisplay   = 29.5f;
    int       m_maxCommandHistory = 128;
    bool      m_startOpen         = false;
};

//----------------------------------------------------------------------------------------------------
/// @brief
/// Class for a dev console that allows entering text and executing commands.
/// Can be toggled with tilde ('~') and renders within a transparent box with configurable bounds.
/// Other features include specific coloring for different lines of text and a blinking insertion point.
class DevConsole
{
public:
    explicit DevConsole(sDevConsoleConfig const& config);
    ~DevConsole() = default;
    void StartUp();
    void Shutdown();
    void BeginFrame();
    void EndFrame();

    void Execute(String const& consoleCommandText, bool echoCommand = true);
    void AddLine(Rgba8 const& color, String const& text);
    void Render(AABB2 const& bounds, Renderer* rendererOverride = nullptr);
    void PasteFromClipboard();

    eDevConsoleMode GetMode() const;
    void            SetMode(eDevConsoleMode mode);
    void            ToggleMode(eDevConsoleMode mode);
    bool            IsOpen() const;

    static bool OnWindowKeyPressed(EventArgs& args);
    static bool OnWindowCharInput(EventArgs& args);
    static bool Command_Clear(EventArgs& args);
    static bool Command_Help(EventArgs& args);

    static const Rgba8 ERROR;
    static const Rgba8 WARNING;
    static const Rgba8 INFO_MAJOR;
    static const Rgba8 INFO_MINOR;
    static const Rgba8 INPUT_TEXT;
    static const Rgba8 INPUT_INSERTION_POINT;

protected:
    void Render_OpenFull(AABB2 const& bounds, Renderer& renderer, BitmapFont const& font, float fontAspect = 1.f);

    sDevConsoleConfig m_config;
    eDevConsoleMode   m_mode = HIDDEN;
    // All lines added to the dev console since the last time it was cleared.
    std::vector<sDevConsoleLine> m_lines;     //TODO: support a max limited # of lines (e.g. fixed circular buffer)
    int                          m_frameNumber = 0;

    // True if the dev console is currently visible and accepting input.
    bool m_isOpen = false;

    // Our current line of input text.
    String m_inputText;

    // Index of the insertion point in our current input text.
    int   m_insertionPointPosition = 0;
    float m_inputTextPosition      = 0;


    bool       m_insertionPointVisible    = false;  // True if our insertion point is currently in the visible phase of blinking.
    Timer*     m_insertionPointBlinkTimer = nullptr;// Timer for controlling insertion point visibility.
    StringList m_commandHistory;                // History of all commands executed.

    // Our current index in our history of commands as we are scrolling.
    int m_historyIndex = -1;

    bool m_isCtrlPressed = false;
};
