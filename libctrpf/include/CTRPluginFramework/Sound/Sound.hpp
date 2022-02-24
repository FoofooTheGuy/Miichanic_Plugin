#ifndef CTRPLUGINFRAMEWORK_SOUND_SOUND_HPP
#define CTRPLUGINFRAMEWORK_SOUND_SOUND_HPP

#include "types.h"
#include <string>

namespace CTRPluginFramework
{
    class Sound
    {
    public:

        enum class LoadStatus {
            NOT_ALLOCATED = 0,              ///< Data is not allocated and cannot be used.
            SUCCESS = 1,                    ///< Loaded properly and is ready to play.
            INVALID_ARGUMENT = 2,           ///< An invalid argument was passed to the constructor.
            FILE_OPEN_FAILED = 3,           ///< Failed to open the specified file.
            FILE_TOO_LARGE = 4,             ///< The file is too large to fit in the available memory.
            UNKNOWN_FILE_FORMAT = 5,        ///< The specified file is not a valid CWAV file.
            INVAID_INFO_BLOCK = 6,          ///< The INFO block in the CWAV file is invalid or not supported.
            INVAID_DATA_BLOCK = 7,          ///< The DATA block in the CWAV file is invalid or not supported.
            UNSUPPORTED_AUDIO_ENCODING = 8  ///< The audio encoding is not supported.
        };

        /**
         * \brief Default sound constructor with no audio attached to it.
         */
        Sound();

        /**
         * \brief Copy constructor.
         * \param sound Object to make copy from.
         * WARNING: The copy shares the same audio buffer!
         */
        Sound(const Sound& sound);

        /**
         * \brief Move constructor
         * \param sound Object to move from.
         */
        Sound(Sound&& sound) noexcept;

        /**
         * \brief Constructs a Sound object from a BCWAV file.
         * \param bcwavFile Path to the BCWAV file (must fit in memory).
         * \param maxSimultPlays Maximum amount of plays at the same time.
         */
        Sound(const std::string& bcwavFile, int maxSimultPlays = 1);

        /**
         * \brief Constructs a Sound object from a BCWAV file in memory.
         * \param bcwavBuffer Buffer to the BCWAV file.
         * \param maxSimultPlays Maximum amount of plays at the same time.
         */
        Sound(const u8* bcwavBuffer, int maxSimultPlays = 1);

        /**
         * \brief Copy asignation operator.
         * \param sound Object to copy asign from.
         * WARNING: The copy shares the same audio buffer!
        */
        Sound& operator=(const Sound& sound);

        /**
         * \brief Move asignation operator.
         * \param sound Object to move asign from.
        */
        Sound& operator=(Sound&& sound) noexcept;

        /**
         * \brief Get the BCWAV load status. The sound will only play if the load status is SUCCESS.
         * \return Load status from the LoadStatus enum.
        */
        LoadStatus GetLoadStatus();

        /**
         * \brief Sets the sound volume. Changes only apply after the next play.
         * \param volume New volume to set, in the range [0, 1].
        */
        void SetVolume(float volume);

        /**
         * \brief Gets the sound volume.
         * \return Volume value, in the range [0, 1].
        */
        float GetVolume();

        /**
         * \brief Sets the sound pan. Changes only apply after the next play.
         * \param pam New pan to set, in the range [-1, 1]. (Left ear: -1, Right ear: 1).
        */
        void SetPan(float pan);

        /**
         * \brief Gets the pan volume.
         * \return Pan value, in the range [-1, 1] (Left ear; -1, Right ear: 1).
        */
        float GetPan();

        /**
         * \brief Gets the amount of channels stored in the BCWAV file.
         * \return Amount of channels in the BCWAV file.
        */
        u32 GetChannelAmount();

        /**
         * \brief Checks if the BCWAV file is looped.
         * \return True if the BCWAV file is looped, false otherwise.
        */
        bool IsLooped();

        /**
         * \brief Plays the first audio channel in mono from the BCWAV file.
         * \return Whether the operation was successful or not.
        */
        bool Play();

        /**
         * \brief Plays the specified audio channel in mono from the BCWAV file.
         * \param monoChannel Channel to play, in the range [ 0, GetChannelAmount() - 1].
         * \return Whether the operation was successful or not.
        */
        bool Play(int monoChannel);

        /**
         * \brief Plays the specified audio channels in stereo from the BCWAV file.
         * \param leftEarChannel Left ear channel to play, in the range [0, GetChannelAmount() - 1].
         * \param rightEarChannel Right each channel to play, in the range [0, GetChannelAmount() - 1].
         * \return Whether the operation was successful or not.
        */
        bool Play(int leftEarChannel, int rightEarChannel);

        /**
         * \brief Stops all the playing channels.
        */
        void Stop();

        /**
         * \brief Stops the specified mono audio channel.
         * \param monoChannel Channel to stop, in the range [ 0, GetChannelAmount() - 1].
        */
        void Stop(int monoChannel);

        /**
         * \brief Stops the specified stereo channels.
         * \param leftEarChannel Left ear channel to stop, in the range [ 0, GetChannelAmount() - 1].
         * \param rightEarChannel Right ear channel to stop, in the range [ 0, GetChannelAmount() - 1].
        */
        void Stop(int leftEarChannel, int rightEarChannel);

        /// Default destructor.
        ~Sound();

    private:
        /// Internal sound data.
        void*   _soundImpl;
    };
}

#endif