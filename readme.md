# This is a predicable state container for C++ applications.
----

This is a C++20 header-only [redux](https://en.wikipedia.org/wiki/Redux_(JavaScript_library)) implementation.


![CI](https://github.com/fengwang/redux/actions/workflows/ci.yml/badge.svg)

### [Example usage](./test.cpp)

**Create a store**

```cpp
auto store = redux::make_store
(
```

with 4 different reducers:

```cpp
    redux::make_reducers
    (
```

The 1st one coresponds to `increment_action`, which will increase the current shared state by 1:

```cpp
redux::make_reducer<"increment_action">( []( int current_state ){ return current_state + 1;} ),
```

The 2nd one coresponds to `decrement_action`, which will decrease the current shared state by 1:

```cpp
redux::make_reducer<"decrement_action">( []( int current_state ){ return current_state - 1;} ),
```

The 3rd one coresponds to `custom_action`, which will increase the shared state by a `custom_step`:

```cpp
redux::make_reducer<"custom_action">( []( int current_state, int custom_step ){ return current_state + custom_step;} ),
```

And the last one coresponds to `conditional_action`, which will increase or decrease the current shared state by a `custom_step` depending on a `threshold`:

```cpp
redux::make_reducer<"conditional_action">( []( int current_state, int threshold, int custom_step )
{ return  current_state < threshold ? current_state + custom_step : current_state - custom_step; } )
    ),
```

While the shared state is initialized to 0.


```cpp
    0
);
```

This `store` has 3 subscriptions:

The 1st one prints the global state in oct:

```cpp
store.subscribe( []( int state ){ std::cout << "Oct: " << std::oct << state << std::endl; } );
```

The 2nd one prints the global state in dec:

```cpp
store.subscribe( []( int state ){ std::cout << "Dec: " << std::dec << state << std::endl; } );
```

and The last one prints the global state in hex:

```cpp
store.subscribe( []( int state ){ std::cout << "Hex: " << std::hex << state << std::endl; } );
```

Then we can dispatch actions:

Dispatching `increment_action`:

```cpp
store.dispatch<"increment_action">();
```

This will increase state from 0 to 1, and produce output:
```
Oct: 1
Dec: 1
Hex: 1
```


Dispatching `decrement_action`:

```cpp
store.dispatch<"decrement_action">();
```

This will decrease state from 1 to 0, and produce output:
```
Oct: 0
Dec: 0
Hex: 0
```

Dispatching `custom_action` with a parameter `7`:

```cpp
store.dispatch<"custom_action">( 7 );
```

This will increase state from 0 to 7, and produce result

```
Oct: 7
Dec: 7
Hex: 7
```

Dispatching `conditiona_action` with parameter `10` and `10`:

```cpp
store.dispatch<"conditional_action">( 10, 10 );
```

This will increase state from 7 to 17, as the current state is less than 10, and produce result

```
Oct: 21
Dec: 17
Hex: 11
```

### [Bonus] Remove a reducer from a store

Just call `store.remove_reducer<"ACTION_NAME">()` to create a new store without the specified `ACTION_NAME` reducer. For example:

```cpp
auto&& new_store = store.remove_reducer<"custom_action">();
new_store.dispatch<"increment_action">();
new_store.dispatch<"decrement_action">();
//new_store.dispatch<"custom_action">( 7 ); // <-- will triger compile time error
new_store.dispatch<"conditional_action">( 12, 8 );
```

### [Bonus] Append a new reducer to a store

Just call `store.append_reducer<"ACTION_NAME">( ACTION_DETAILS )` to create a new store with an additional reducer. For example:

```cpp
auto&& new_store = store.append_reducer<"custom_action_2">( [](int current_state, int new_custom_step){ return current_state + new_custom_step*7; } );
new_store.dispatch<"custom_action_2">( 7 ); // now possible
```


### [Bonus] Replace a reducer with new actions


Just call `store.replace_reducer<"ACTION_NAME">( NEW_ACTION_DETAILS )` to create a new store with an updated reducer. For example:

```cpp
auto&& new_store = store.replace_reducer<"increment_action">( [](int current_state, int new_custom_step){ return current_state + new_custom_step*7; } );
new_store.dispatch<"increment_action">( 7 );
```

With this new store, invoking increment_action will increase the current state by 7*`step` instead of `step`.


## Test environment

+ gcc-12.2.0
+ Arch Linux 5.15.79-1-lts

## License

AGPL-v3















































