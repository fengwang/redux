#ifndef REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ
#define REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ

#include <functional>
#include <vector>

#include "./meta_structure.hpp"

namespace redux
{
    template< meta::fixed_string tag, typename Action >
    auto make_reducer( Action const& action ) noexcept;

    template<meta::Member ... Reducers>
    auto make_reducers( Reducers const& ... reducers ) noexcept;

    template <meta::Structure Reducers, typename State_Type>
    struct store;

    template< typename S, typename State_Type >
    store<meta::structure<S>, State_Type> make_store( meta::structure<S> const& meta_structure, State_Type const& state, std::vector<std::function<void(State_Type)>> const& subscribers=std::vector<std::function<void(State_Type)>>{} ) noexcept;

    template <meta::Structure Reducers, typename State_Type>
    struct store
    {
        Reducers reducers_;
        State_Type state_;
        std::vector<std::function<void(State_Type)>> subscribers_;

        constexpr store( Reducers const& reducers, State_Type const& state,
                         std::vector<std::function<void(State_Type)>> const& subscribers=std::vector<std::function<void(State_Type)>>{}  ) noexcept :
                         reducers_{ reducers }, state_{ state }, subscribers_{subscribers} { }

        template< typename Subscriber >
        void subscribe( Subscriber const& subscriber ) noexcept
        {
            subscribers_.emplace_back( std::function<void(State_Type)>{subscriber} );
        }

        template< meta::fixed_string tag, typename ... Args >
        void dispatch( Args const& ... args ) noexcept
        {
            state_ = reducers_.template read<tag>()( state_, args... );
            for ( auto const& subscriber : subscribers_ )
                subscriber( state_ );
        }

        State_Type const get_state() const noexcept
        {
            return state_;
        }

        template<meta::fixed_string tag, typename New_Action >
        auto append_reducer( New_Action const& new_action ) const noexcept
        {
            return make_store( reducers_.template update<tag>(new_action),  state_, subscribers_ );
        }

        template<meta::fixed_string tag, typename New_Action >
        auto replace_reducer( New_Action const& new_action ) const noexcept
        {
            return make_store( reducers_.template update<tag>(new_action),  state_, subscribers_ );
        }

        template<meta::fixed_string tag>
        auto remove_reducer() const noexcept
        {
            return make_store( reducers_.template remove<tag>(),  state_, subscribers_ );
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
    store<meta::structure<S>, State_Type> make_store( meta::structure<S> const& meta_structure, State_Type const& state, std::vector<std::function<void(State_Type)>> const& subscribers ) noexcept
    {
        return store{ meta_structure, state, subscribers };
    }

} // namespace redux

#endif//REDUX_H_INCLUDED_DOFSPIASDLFKJASDDFLKJASDDFOIUJ4RLKJAFSDLKJSAFDKLJSADFJ

