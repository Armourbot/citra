// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <memory>

#include "common/common_types.h"
#include "common/make_unique.h"

#include "core/file_sys/archive_romfs.h"
#include "core/file_sys/directory_romfs.h"
#include "core/file_sys/file_romfs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSys namespace

namespace FileSys {

Archive_RomFS::Archive_RomFS(const Loader::AppLoader& app_loader) {
    // Load the RomFS from the app
    if (Loader::ResultStatus::Success != app_loader.ReadRomFS(raw_data)) {
        LOG_ERROR(Service_FS, "Unable to read RomFS!");
    }
}

std::unique_ptr<FileBackend> Archive_RomFS::OpenFile(const Path& path, const Mode mode) const {
    return Common::make_unique<File_RomFS>(this);
}

bool Archive_RomFS::DeleteFile(const Path& path) const {
    LOG_WARNING(Service_FS, "Attempted to delete a file from ROMFS.");
    return false;
}

bool Archive_RomFS::RenameFile(const Path& src_path, const Path& dest_path) const {
    LOG_WARNING(Service_FS, "Attempted to rename a file within ROMFS.");
    return false;
}

bool Archive_RomFS::DeleteDirectory(const Path& path) const {
    LOG_WARNING(Service_FS, "Attempted to delete a directory from ROMFS.");
    return false;
}

ResultCode Archive_RomFS::CreateFile(const Path& path, u32 size) const {
    LOG_WARNING(Service_FS, "Attempted to create a file in ROMFS.");
    // TODO: Verify error code
    return ResultCode(ErrorDescription::NotAuthorized, ErrorModule::FS, ErrorSummary::NotSupported, ErrorLevel::Permanent);
}

bool Archive_RomFS::CreateDirectory(const Path& path) const {
    LOG_WARNING(Service_FS, "Attempted to create a directory in ROMFS.");
    return false;
}

bool Archive_RomFS::RenameDirectory(const Path& src_path, const Path& dest_path) const {
    LOG_WARNING(Service_FS, "Attempted to rename a file within ROMFS.");
    return false;
}

std::unique_ptr<DirectoryBackend> Archive_RomFS::OpenDirectory(const Path& path) const {
    return Common::make_unique<Directory_RomFS>();
}

ResultCode Archive_RomFS::Format(const Path& path) const {
    LOG_WARNING(Service_FS, "Attempted to format ROMFS.");
    return UnimplementedFunction(ErrorModule::FS);
}

} // namespace FileSys
