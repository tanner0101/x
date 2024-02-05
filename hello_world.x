struct Int {
    raw: Int64
}

struct String {
    raw: Pointer<UInt8>
}

extern fn printf(s: Pointer<UInt8>, ...) -> Int32
extern fn puts(s: Pointer<UInt8>) -> Int32

fn print(string: String) {
    printf(string.raw)
}

fn meaningOfLife() -> Int {
    return 42
}

fn test() -> String {
    return "test"
}

struct Planet {
    name: String
    moons: Int
}

fn greet(name: String) {
    print("Hello, ")
    print(name)
    print("!\n")
}

fn main() {
    var earth = Planet("Earth", 1)
    print(erth.name)
    var mars = Planet("Mars", 2)
    greet(mars.name)
    print(test())

    printf("Earth has %d moons\n".raw, earth.moons.raw)
}

