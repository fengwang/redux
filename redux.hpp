#ifndef REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ
#define REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ

#include <functional>
#include <vector>

namespace redux
{

    template <typename Reducer, typename State_Type>
    struct store
    {
        Reducer reducer_;
        State_Type state_;
        std::vector<std::function<void(State_Type)>> subscribers_;

        store( Reducer const& reducer, State_Type const& state ) noexcept : reducer_{ reducer }, state_{ state } { }

        template< typename Subscriber >
        void subscribe( Subscriber const& subscriber )
        {
            subscribers_.push_back( std::function<void(State_Type)>{subscriber} );
        }

        template< typename Action_Type >
        void dispatch( Action_Type const& action ) noexcept
        {
            state_ = reducer_( state_, action );
            for ( auto const& subscriber : subscribers_ )
                subscriber( state_ );
        }

        State_Type const state() const noexcept
        {
            return state_;
        }

        State_Type& state() noexcept
        {
            return state_;
        }

    }; // struct store

} // namespace redux

#endif//REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ

#if 0

struct increment_action{};
struct decrement_action{};

struct reducer
{
    template< typename T >
    T operator()( T state, increment_action ) const noexcept
    {
        return state + 1;
    }

    template< typename T >
    T operator()( T state, decrement_action ) const noexcept
    {
        return state - 1;
    }

};

redux::store{ reducer{}, 0 }; // create a reducer with initial parameter 0
auto const& loger = []( int state ){ std::cout << state << std::endl; };
store.subscribe( loger );
store.dispatch( increment_action{} );
store.dispatch( increment_action{} );
store.dispatch( decrement_action{} );

#endif


