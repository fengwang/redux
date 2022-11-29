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

    store.dispatch<"increment_action">();
    store.dispatch<"decrement_action">();
    store.dispatch<"custom_action">( 7 );
    store.dispatch<"conditional_action">( 10, 10 );
    store.dispatch<"conditional_action">( 11, 9 );
    store.dispatch<"conditional_action">( 12, 8 );

    std::cout << "Our store holds a state " << std::dec << store.state() << std::endl;

    return 0;
}

