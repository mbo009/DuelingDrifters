class loadingTexturesError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error in loading textures!";
    }
};