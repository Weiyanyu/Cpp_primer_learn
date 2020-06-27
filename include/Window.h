#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>
#include <iostream>

// ------ class of window mgr ------

class Screen;

class Window_mgr {
public:
    static const std::string::size_type DEFAULT_HEIGHT;
    static const std::string::size_type DEFAULT_WIDTH;


    using screenIndex = std::vector<Screen>::size_type;
    void clear(screenIndex i);
    Window_mgr &addScreen(Screen &screen);
    void display(screenIndex i);
    void display();

private:
    std::vector<Screen> screens;


};

// ------ class of window screen ------

class Screen {
    friend void Window_mgr::clear(screenIndex);
public:
    typedef std::string::size_type pos;

    //constructor
    Screen() = default;
    Screen(pos h, pos w, char c):
            height(h), width(w), content(h * w, c) { }
    Screen(pos h, pos w) : 
            height(h), width(w), content("") { }
    

    //member function
        
    inline char get() const 
    {
        access_ctr++;
        return content[cursor]; 
    }

    inline pos size() const;

    inline char get(pos r, pos c) const;
    inline Screen &move(pos r, pos c);
    inline Screen &set(char ch);
    inline Screen &set(pos r, pos c, char ch);
    inline const Screen &display(std::ostream &os) const 
    {
        do_display(os);
        return *this;
    }

    inline Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }
    

private:
    pos cursor = 0;
    pos height = 0;
    pos width = 0;
    std::string content;

    mutable size_t access_ctr;

    //member function
    void do_display(std::ostream &os) const 
    {
        os << content;
    }
};


// ------ inline function of window screen ------

inline
void Window_mgr::clear(screenIndex i) 
{
    if (i >= screens.size()) {
        return;
    }
    Screen &s = screens[i];
    s.content = std::string(s.height * s.width, ' ');
}

inline
void Window_mgr::display() {
    for (auto screen : screens) {
        screen.display(std::cout);
        std::cout << "\n";
    }
}

inline
void Window_mgr::display(screenIndex i) {
    screens[i].display(std::cout);
    std::cout << "\n";
}

// ------ inline function of window screen ------

inline 
char Screen::get(pos r, pos c) const 
{
    access_ctr++;
    pos row = r * this->width;
    return this->content[row + c];
}

inline 
Screen &Screen::move(pos r, pos c) 
{
    access_ctr++;
    pos row = r * this->width;
    this->cursor = row + c;
    return *this;
}

inline 
Screen &Screen::set(char ch) 
{
    this->content[cursor] = ch;
    return *this;
}

inline
Screen &Screen::set(pos r, pos c, char ch)
{
    pos row = r * this->width;
    this->content[row + c] = ch;
    return *this;
}


inline
Screen::pos Screen::size() const 
{
    return height * width;
}

#endif