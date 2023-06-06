/**
 * @brief Return exception when the texture fails to load
 * 
 */
class failedToLoadTexture : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load texture!";
    }
};

/**
 * @brief Return exception if the asset path is not found
 * 
 */
class failedToGetAssetPath : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to get asset path!";
    }
};

/**
 * @brief Return exception when the font fails to load
 * 
 */
class failedToLoadFont : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load font!";
    }
};

/**
 * @brief Return exception when the sound fails to load
 * 
 */
class failedToLoadSound : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Failed to load sound!";
    }
};