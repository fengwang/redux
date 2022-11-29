#ifndef REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ
#define REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ

#include <functional>
#include <vector>

#include "./meta_structure.hpp"

namespace redux
{

    template <meta::Structure Reducers, typename State_Type>
    struct store
    {
        Reducers reducers_;
        State_Type state_;
        std::vector<std::function<void(State_Type)>> subscribers_;

        store( Reducers const& reducers, State_Type const& state ) noexcept : reducers_{ reducers }, state_{ state } { }

        template< typename Subscriber >
        void subscribe( Subscriber const& subscriber )
        {
            subscribers_.push_back( std::function<void(State_Type)>{subscriber} );
        }

        template< meta::fixed_string tag, typename ... Args >
        void dispatch( Args const& ... args ) noexcept
        {
            state_ = reducers_.template read<tag>()( state_, args... );
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

    template< meta::fixed_string tag, typename Action >
    auto make_reducer( Action const& action ) noexcept
    {
        return meta::make_member<tag>( action );
    }

    template<meta::Member ... Reducers>
    auto make_reducers( Reducers const& ... reducers ) noexcept
    {
        return meta::make_struct( reducers... );
    }

    template< typename S, typename State_Type >
    store<meta::structure<S>, State_Type> make_store( meta::structure<S> const& meta_structure, State_Type const& state ) noexcept
    {
        return store{ meta_structure, state };
    }

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


