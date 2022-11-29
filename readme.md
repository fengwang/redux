# This is a predicable state manager for C++ applications.
----

Example usage:

**Create a store** with

```cpp
auto store = redux::make_store
(
```

with 4 different reducers:

```cpp
    redux::make_reducers
    (
```

The 1st one coresponds to `increment_action`, and will increase the current shared state by 1:

```cpp
        redux::make_reducer<"increment_action">( []( int current_state ){ return current_state + 1;} ),
```

The 2nd one coresponds to `decrement_action`, and will decrease the current shared state by 1:

```cpp
        redux::make_reducer<"decrement_action">( []( int current_state ){ return current_state - 1;} ),
```

The 3rd one coresponds to `custom_action`, and will increase the shared state by a `custom_step`:

```cpp
        redux::make_reducer<"custom_action">( []( int current_state, int custom_step ){ return current_state + custom_step;} ),
```

And the last one coresponds to `conditional_action`, and will increase or decrease the current shared state by a `custom_step` depending on a `threshold`:

```cpp
        redux::make_reducer<"conditional_action">( []( int current_state, int threshold, int custom_step ){ return  current_state < threshold ? current_state + custom_step : current_state - custom_step; } )
    ),
```

And the shared state is initialized to 0.


```cpp
    0
);
```













