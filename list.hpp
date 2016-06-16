#pragma once

template <class... Elems>
struct List
{
    enum {
        len = sizeof...(Elems)
    };
};

// ----------------------------------------------------------------------------

template <class List>
struct Car;

template <class X, class... Xs>
struct Car<List<X, Xs...>>
{
    using Type = X;
};

template <class List>
using car_t = typename Car<List>::Type;

// ----------------------------------------------------------------------------

template <class List>
struct Cdr;

template <class X, class... Xs>
struct Cdr<List<X, Xs...>>
{
    using Type = List<Xs...>;
};

template <class List>
using cdr_t = typename Cdr<List>::Type;

// ----------------------------------------------------------------------------

template <unsigned pos, class List>
struct Get
{
    static_assert(List::len > pos, "Index is out of range");
    using Type = typename Get<pos - 1, cdr_t<List>>::Type;
};

template <class List>
struct Get<0, List>
{
    using Type = car_t<List>;
};

template <unsigned pos, class List>
using get_t = typename Get<pos, List>::Type;

// ----------------------------------------------------------------------------

template <class Elem, class List>
struct Cons;

template <class Elem, class... Xs>
struct Cons<Elem, List<Xs...>>
{
    using Type = List<Elem, Xs...>;
};

template <class Elem, class List>
using cons_t = typename Cons<Elem, List>::Type;

// ----------------------------------------------------------------------------

template <unsigned pos, class Elem, class List>
struct Put
{
    using Type = cons_t<car_t<List>, typename Put<pos - 1, Elem, cdr_t<List>>::Type>;
};

template <class Elem, class List>
struct Put<0, Elem, List>
{
    using Type = cons_t<Elem, cdr_t<List>>;
};

template <unsigned pos, class Elem, class List>
using put_t = typename Put<pos, Elem, List>::Type;

//-----------------------------------------------------------------------------

template <unsigned len, class Elem>
struct CreateList
{
    using Type = cons_t<Elem, typename CreateList<len - 1, Elem>::Type>;
};

template <class Elem>
struct CreateList<0, Elem>
{
    using Type = List<>;
};

template <unsigned len, class Elem>
using create_list_t = typename CreateList<len, Elem>::Type;
