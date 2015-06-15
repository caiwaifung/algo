#include "message.h"
#include "mutexes.h"
#include <bits/stdc++.h>

/*** START OF TEMPLATE CODE ***/

namespace msg
{

template<typename T> class serialize;

template<>
class serialize<char>
{
public:
    static char get(int source) { return GetChar(source); }
    static void put(int target, char value) { PutChar(target, value); }
};

template<>
class serialize<int>
{
public:
    static int get(int source) { return GetInt(source); }
    static void put(int target, int value) { PutInt(target, value); }
};

template<>
class serialize<long long>
{
public:
    static long long get(int source) { return GetLL(source); }
    static void put(int target, long long value) { PutLL(target, value); }
};

template<typename T>
class serialize<std::vector<T> >
{
public:
    static std::vector<T> get(int source)
    {
        long long size = GetLL(source);
        std::vector<T> out;
        out.reserve(size);
        for (long long i = 0; i < size; i++)
            out.push_back(serialize<T>::get(source));
        return out;
    }

    static void put(int target, const std::vector<T> &value)
    {
        PutLL(target, value.size());
        for (std::size_t i = 0; i < value.size(); i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename T, std::size_t N>
class serialize<std::array<T, N> >
{
public:
    static std::array<T, N> get(int source)
    {
        std::array<T, N> out;
        for (std::size_t i = 0; i < N; i++)
            out[i] = serialize<T>::get(source);
        return out;
    }

    static void put(int target, const std::array<T, N> &value)
    {
        for (std::size_t i = 0; i < N; i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename A, typename B>
class serialize<std::pair<A, B> >
{
public:
    static std::pair<A, B> get(int source)
    {
        A a{serialize<A>::get(source)};
        B b{serialize<B>::get(source)};
        return std::make_pair(std::move(a), std::move(b));
    }

    static void put(int target, const std::pair<A, B> &value)
    {
        serialize<A>::put(target, value.first);
        serialize<B>::put(target, value.second);
    }
};

namespace detail
{

template<int P, typename... Args>
class serialize_tuple
{
private:
    typedef typename std::tuple_element<P, std::tuple<Args...> >::type element_type;
public:
    static void get(int source, std::tuple<Args...> &out)
    {
        serialize_tuple<P - 1, Args...>::get(source, out);
        std::get<P>(out) = serialize<element_type>::get(source);
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        serialize_tuple<P - 1, Args...>::put(target, value);
        serialize<element_type>::put(target, std::get<P>(value));
    }
};

template<typename... Args>
class serialize_tuple<-1, Args...>
{
public:
    static void get(int, std::tuple<Args...> &) {}
    static void put(int, const std::tuple<Args...> &) {}
};

} // namespace detail

template<typename... Args>
class serialize<std::tuple<Args...> >
{
public:
    static std::tuple<Args...> get(int source)
    {
        std::tuple<Args...> out;
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::get(source, out);
        return out;
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::put(target, value);
    }
};

template<typename T>
static T get(int source)
{
    return serialize<T>::get(source);
}

template<typename T>
static void get(int source, T &data)
{
    data = serialize<T>::get(source);
}

template<typename T>
static void put(int target, const T &value)
{
    serialize<T>::put(target, value);
}

template<typename T>
static T receive(int source)
{
    source = Receive(source);
    return get<T>(source);
}

template<typename T>
static int receive(int source, T &data)
{
    source = Receive(source);
    data = get<T>(source);
    return source;
}

template<typename T>
static void send(int target, const T &value)
{
    put<T>(target, value);
    Send(target);
}

class range_comm
{
private:
    int first;
    int last;

public:
    explicit range_comm(int last) : first(0), last(last) {}
    range_comm(int first, int last) : first(first), last(last) {}

    template<typename T, typename Op = std::plus<T> >
    T reduce(int root, const T &value, const Op &op = Op()) const
    {
        if (MyNodeId() == root)
        {
            T ans = value;
            for (int i = first; i < last; i++)
                if (i != root)
                    ans = op(ans, receive<T>(i));
            return ans;
        }
        else
        {
            send(root, value);
            return T();
        }
    }

    template<typename T>
    T broadcast(int root, const T &value) const
    {
        if (MyNodeId() == root)
        {
            for (int i = first; i < last; i++)
            {
                if (i != root)
                    send(i, value);
            }
            return value;
        }
        else
            return receive<T>(root);
    }

    template<typename T, typename Op = std::plus<T> >
    T allreduce(const T &value, const Op &op = Op()) const
    {
        T mid = reduce(first, value, op);
        return broadcast(first, value);
    }

    template<typename T>
    std::vector<T> gather(int root, const T &value)
    {
        std::vector<T> ans;
        if (MyNodeId() == root)
        {
            ans.reserve(last - first);
            for (int i = first; i < last; i++)
                if (i == root)
                    ans.push_back(value);
                else
                    ans.push_back(receive<T>(i));
        }
        else
            send(root, value);
        return ans;
    }

    template<typename T>
    T scatter(int root, const std::vector<T> &values)
    {
        if (MyNodeId() == root)
        {
            assert(values.size() == size_t(last - first));
            for (int i = first; i < last; i++)
                if (i != root)
                    send(i, values[i - first]);
            return values[root];
        }
        else
        {
            return receive<T>(root);
        }
    }
};

} // namespace msg

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef complex<double> pnt;
typedef pair<int, int> pii;

#define RA(x) begin(x), end(x)
#define FE(i, x) for (auto i = begin(x); i != end(x); ++i)
#define SZ(x) ((int) (x).size())

/*** END OF TEMPLATE CODE ***/

struct cell
{
    int reach_left;
    int reach_right;
    int reach_dead;
};

namespace msg
{

template<>
class serialize<cell>
{
public:
    static cell get(int source)
    {
        cell ans;
        ans.reach_left = serialize<int>::get(source);
        ans.reach_right = serialize<int>::get(source);
        ans.reach_dead = serialize<int>::get(source);
        return ans;
    }

    static void put(int target, const cell &value)
    {
        serialize<int>::put(target, value.reach_left);
        serialize<int>::put(target, value.reach_right);
        serialize<int>::put(target, value.reach_dead);
    }
};

} // namespace msg

static int apply(vector<bool> &taken, int m)
{
    if (m > 0)
    {
        taken[m] = true;
        return m;
    }
    else
    {
        taken[-m] = false;
        return -m;
    }
}

#define MAX_MUTEX 100001

int main(int argc, const char **argv)
{
    int nodes = NumberOfNodes();
    int rank = MyNodeId();
    int R = NumberOfOperations(0);
    int C = NumberOfOperations(1);
    if (nodes > R)
    {
        nodes = R;
        if (rank >= nodes)
            return 0;
    }
    msg::range_comm world(0, nodes);

    int R0 = rank * (ll) R / nodes;
    int R1 = (rank + 1) * (ll) R / nodes;
    vector<bool> rtaken(MAX_MUTEX);
    for (int i = 0; i < R0; i++)
        apply(rtaken, GetOperation(0, i));

    vector<int> lo(C + 1), hi(C + 1);
    for (int i = 0; i < C; i++)
    {
        lo[i] = i;
        hi[i] = i + 1;
    }
    vector<pii> killers;
    vector<bool> is_open(C + 1, true);
    for (int i = R0; i < R1; i++)
    {
        apply(rtaken, GetOperation(0, i));
        vector<bool> ctaken(MAX_MUTEX);
        int overlaps = 0;
        for (int j = 0; j <= C; j++)
        {
            if (overlaps > 0)
            {
                if (j < C && lo[j] < hi[j] && is_open[j] && !is_open[j + 1])
                {
                    int score = i + j + 2;
                    killers.emplace_back(lo[j], score);
                    killers.emplace_back(hi[j], -score);
                    //cerr << "Adding killer at row " << i << ", col " << j << "\n";
                }
                lo[j] = C + 2;
                hi[j] = -1;
            }
            else
            {
                if (j > 0)
                {
                    lo[j] = min(lo[j], lo[j - 1]);
                    hi[j] = max(hi[j], hi[j - 1]);
                }
            }
            is_open[j] = overlaps == 0;

            if (j < C)
            {
                int m = apply(ctaken, GetOperation(1, j));
                if (rtaken[m])
                    overlaps += ctaken[m] ? 1 : -1;
            }
        }
    }

    if (R1 < R)
    {
        apply(rtaken, GetOperation(0, R1));
        vector<bool> ctaken(MAX_MUTEX);
        int overlaps = 0;
        for (int j = 0; j <= C; j++)
        {
            if (overlaps > 0)
            {
                if (j < C && lo[j] < hi[j] && is_open[j] && !is_open[j + 1])
                {
                    int score = R1 + j + 2;
                    killers.emplace_back(lo[j], score);
                    killers.emplace_back(hi[j], -score);
                    //cerr << "Adding killer at row " << R1 << ", col " << j << "\n";
                }
            }
            if (j < C)
            {
                int m = apply(ctaken, GetOperation(1, j));
                if (rtaken[m])
                    overlaps += ctaken[m] ? 1 : -1;
            }
        }
    }

    sort(RA(killers));
    int k = 0;

    vector<cell> cells(C + 1);
    multiset<int> kill_depth;
    for (int j = 0; j <= C; j++)
    {
        while (k < SZ(killers) && killers[k].first <= j)
        {
            int score = killers[k].second;
            if (score > 0)
                kill_depth.insert(score);
            else
                kill_depth.erase(kill_depth.find(-score));
            k++;
        }
        cells[j].reach_left = lo[j];
        cells[j].reach_right = hi[j];
        cells[j].reach_dead = kill_depth.empty() ? INT_MAX : *kill_depth.begin();
    }

    auto collected = world.gather(0, cells);
    if (rank == 0)
    {
        int ans = INT_MAX;
        vector<int> reach(C + 1, 1);
        for (const vector<cell> &rs : collected)
        {
            for (int j = 0; j <= C; j++)
                if (reach[j])
                    ans = min(ans, rs[j].reach_dead);
            vector<int> acc(C + 2);
            partial_sum(RA(reach), acc.begin() + 1);
            for (int j = 0; j <= C; j++)
            {
                if (rs[j].reach_left < rs[j].reach_right)
                    reach[j] = (acc[rs[j].reach_right] - acc[rs[j].reach_left]) ? 1 : 0;
                else
                    reach[j] = false;
            }
        }
        if (ans == INT_MAX)
            cout << "OK\n";
        else
            cout << ans << '\n';
    }

    return 0;
}
