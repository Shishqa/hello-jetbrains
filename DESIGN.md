# Solution design

The solution to the problem consists of three main parts:

- Xlib C++ wrapper
- OpenGL C++ wrapper
- App itself

We need wrappers to respect RAII idiom in C++ and encapsulate some logic for 
convenient usage.

## Directory structure

```
src/
├── shaders/         <--- GLSL shaders
│   └── ...
├── tiny-graphics/   <--- Simple library connecting Xlib and OpenGL
│   ├── tiny-opengl/ <--- OpenGL wrapper
│   │   └── ...
│   ├── tiny-xlib/   <--- Xlib wrapper
│   │   └── ...
│   └── ...
└── wheels/          <--- Utility library 
    └── ...
```

## Usage

To open X-Server connection, just create an object of `X11::Display` class. 
Connection will close with destruction of object. To initialize visual 
attributes create a `X11::Visual` object.

```C++
X11::Display display;
X11::Visual visual(display.Get());

...

::Display* handle = display.Get();

...

::XVisualInfo* vi = visual.VisualInfo();
```

To open simple X window, create a `X11::Window` object. It will map to display 
immediately. To create window with graphics context, create a `tg::Window` object. 
It has GLX graphics context bind to the `X11::Window` inside.

### Running event loop

To manage events coming from X Server there is the `X11::EventDispatcher` class. 
It has method `RunLoop()` to run the event loop inside. To listen for the events
you can subscribe your window to the current event dispatcher with
`dispatcher.AddListener(window)`.


To handle specific events there is an `event_mask` field in the event dispatcher.
Each window can override virtual handlers for different types of events:
`OnExpose, OnDestroy, OnMouseClicked, etc.` There is a virtual method `OnEvent` to 
handle the rest of the events and design your logic if you wish.

```C++

class MyCustomWindow : public tg::Window {
[...]
  void OnDestroy() override {
    std::cout << "I am being destroyed :(";
  }
};

...
// in main()

X11::EventDispatcher dispatcher(display.Get(), 
    ExposureMask | PointerMotionMask);

tg::Window win(display.Get(), visual, tg::Size2{500, 500}, tg::Pos2{0, 0});

dispatcher.AddListener(&win);
dispatcher.RunLoop();
```

## Things to improve

- Error dispatching (throwing exceptions is not very good in such low level libraries)
- Do some work with managing vertex buffers in OpenGL
- Write more comments in source code despite the fact that it is quite self-descriptive
