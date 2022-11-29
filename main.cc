#include "./redux.hpp"
#include <iostream>

struct increment_action{};
struct decrement_action{};
struct increment_10_action{};
struct custom_action{ int steps_; };

struct reducer
{
    int operator()( int state, increment_action ) const noexcept
    {
        return state + 1;
    }

    int operator()( int state, increment_10_action ) const noexcept
    {
        return state + 10;
    }

    int operator()( int state, decrement_action ) const noexcept
    {
        return state - 1;
    }

    int operator()( int state, custom_action const& ca ) const noexcept
    {
        return state += ca.steps_;
    }

};

int main()
{
    redux::store st{ reducer{}, 0 }; // create a reducer with initial parameter 0
    auto const& loger = []( int state ){ std::cout << state << std::endl; };
    st.subscribe( loger );
    st.dispatch( increment_action{} );
    st.dispatch( increment_action{} );
    st.dispatch( decrement_action{} );
    st.dispatch( increment_10_action{} );
    st.dispatch( custom_action{-3} );
    st.dispatch( custom_action{3} );

    return 0;
}

