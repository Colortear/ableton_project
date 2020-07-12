template <typename C, typename ...Refs>
void    CommandProcessor::registerCommand(std::string name, Refs&... refs)
{
    this->_commands.insert(std::make_pair(name, std::unique_ptr<Command>(new C(refs...))));
}
