#pragma once

template <typename Value>
struct std::formatter<std::vector<Value>>
{
    constexpr auto parse(auto &ctx)
    {
        return f.parse(ctx);
    }
    auto format(const std::vector<Value> &v, auto &ctx) const
    {
        auto &&out = ctx.out();
        std::format_to(out, "[");
        if (v.size() > 0)
            f.format(v[0], ctx);
        for (int i = 1; i < v.size(); ++i)
        {
            std::format_to(out, ", ");
            f.format(v[i], ctx);
        }
        return std::format_to(out, "]");
    }
    std::formatter<Value> f;
};
template <typename Value>
struct std::formatter<std::vector<std::vector<Value>>>
{
    constexpr formatter() : f() {}
    constexpr auto parse(auto &ctx)
    {
        return f.parse(ctx);
    }
    auto format(const std::vector<std::vector<Value>> &v, auto &ctx) const
    {
        auto &&out = ctx.out();
        std::format_to(out, "[\n\t");
        if (v.size() > 0)
            f.format(v[0], ctx);
        for (int i = 1; i < v.size(); ++i)
        {
            std::format_to(out, ",\n\t");
            f.format(v[i], ctx);
        }
        return std::format_to(out, "\n]");
    }
    std::formatter<vector<Value>> f;
};
