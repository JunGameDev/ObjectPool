# Simple Object Pool

## Example
```cpp
ObjectPool pool(16);

// Adding game objects
pool.AddGameObject("Cat",    { 10, 11, 12 },        { 13, 14 });
pool.AddGameObject("Dog",    { 100, 110, 120 },     { 130, 140 });
pool.AddGameObject("Rat",    { 1000, 1100, 1200 },  { 1300, 1400 });
pool.AddGameObject("Rabbit", { 1200, 100, 3200 },   { 3300, 3400 });

// Destroying game objects
pool.DestroyGameObject(1);  // dog should be gone
pool.DestroyGameObject(1);  // rat should be gone
pool.DestroyGameObject(0);  // cat should be gone

// Printing game objects' status
pool.PrintGameObjects();

```
