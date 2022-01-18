﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <unordered_map>
#include <algorithm>
#include <vector>

class ToastRegistrationManager
{
public:
    ToastRegistrationManager()
    {
        m_toastStorage = winrt::Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(
            L"Toast", winrt::Windows::Storage::ApplicationDataCreateDisposition::Always);

        for (auto pair : m_toastStorage.Values())
        {
            Add(pair.Key().c_str(), pair.Value().as<winrt::hstring>().c_str());
        }
    };

    void Add(std::wstring const& processName, std::wstring const& toastAppId);

    void Remove(std::wstring const& processName);

    std::wstring GetToastRegistration(std::wstring const& processName);

private:
    winrt::Windows::Storage::ApplicationDataContainer m_toastStorage{ nullptr };

    std::unordered_map<std::wstring, std::wstring> m_registrationMap = {};
    wil::srwlock m_lock;
};
