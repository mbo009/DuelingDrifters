class failedToLoadTexture : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load texture!";
    }
};

class failedToGetAssetPath : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to get asset path!";
    }
};

class failedToLoadFont : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load font!";
    }
};

class failedToLoadSound : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load sound!";
    }
};