#include "./redux.hpp"
#include <iostream>

int main()
{
    auto store = redux::make_store
    (
        redux::make_reducers
        (
            redux::make_reducer<"increment_action">( []( int current_state ){ return current_state + 1;} ),
            redux::make_reducer<"decrement_action">( []( int current_state ){ return current_state - 1;} ),
            redux::make_reducer<"custom_action">( []( int current_state, int custom_step ){ return current_state + custom_step;} ),
            redux::make_reducer<"conditional_action">( []( int current_state, int threshold, int custom_step ){ return  current_state < threshold ? current_state + custom_step : current_state - custom_step; } )
        ),
        0 // initial state
    );

    store.subscribe( []( int state ){ std::cout << "Oct: " << std::oct << state << std::endl; } );
    store.subscribe( []( int state ){ std::cout << "Dec: " << std::dec << state << std::endl; } );
    store.subscribe( []( int state ){ std::cout << "Hex: " << std::hex << state << std::endl; } );

    std::cout << "Increase:\n";
    store.dispatch<"increment_action">();
    std::cout << "Decrease:\n";
    store.dispatch<"decrement_action">();
    std::cout << "Custom(7):\n";
    store.dispatch<"custom_action">( 7 );
    std::cout << "Condition(10, 10):\n";
    store.dispatch<"conditional_action">( 10, 10 );
    std::cout << "Condition(11, 9):\n";
    store.dispatch<"conditional_action">( 11, 9 );
    std::cout << "Condition(12, 8):\n";
    store.dispatch<"conditional_action">( 12, 8 );
    std::cout << "Condition(13, 7):\n";
    store.dispatch<"conditional_action">( 13, 7 );

    std::cout << "Our store holds a state " << std::dec << store.get_state() << std::endl;

    // remove 'custom_action' reducer from the store
    {
        auto&& new_store = store.remove_reducer<"custom_action">();
        new_store.dispatch<"increment_action">();
        new_store.dispatch<"decrement_action">();
        //new_store.dispatch<"custom_action">( 7 ); // <-- will triger compile time error
        new_store.dispatch<"conditional_action">( 12, 8 );
        std::cout << "Our store holds a state " << std::dec << new_store.get_state() << std::endl;
    }

    // append a new 'custom_action_2' reducer to the store
    {
        auto&& new_store = store.append_reducer<"custom_action_2">( [](int current_state, int new_custom_step){ return current_state + new_custom_step*7; } );
        new_store.dispatch<"custom_action">( 7 );
        new_store.dispatch<"custom_action_2">( 7 );
        std::cout << "Our store holds a state " << std::dec << new_store.get_state() << std::endl;
    }

    // replace increment_action
    {
        auto&& new_store = store.replace_reducer<"increment_action">( [](int current_state, int new_custom_step){ return current_state + new_custom_step*7; } );
        new_store.dispatch<"increment_action">( 7 );
        std::cout << "Our store holds a state " << std::dec << new_store.get_state() << std::endl;
    }






    return 0;
}

