// Public composition

class Engine  {
public:
    void start() const {}
    void rev() const {}
    void stop() const {}
    Engine(){}
    ~Engine(){}
    void print(){}
};

class Wheel  {
public:
    void inflate(int psi) const {}
    Wheel(){}
    ~Wheel(){}
    void print(){}
};

class Window  {
public:
    void rollup() const {}
    void rolldown() const {}
    Window(){}
    ~Window(){}
    void print(){}
};

class Door  {
public:
    Window window;
    void open() const {}
    void close() const {}
    Door(){}
    ~Door(){}
    void print(){}
};

class Car  {
public:
    Engine engine;
    Wheel wheel[4];
    Door left, right; // 2-door
    Car(){}
    ~Car(){}
    void print(){}
};

int main() {
    Car car;
    car.left.window.rollup();
    car.wheel[0].inflate(72);
}
