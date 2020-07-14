template <typename O>
std::optional<O>    make_optional_if(bool argument, O value)
{
    return argument ? std::optional<O>(value) : std::nullopt;
}
