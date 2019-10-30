#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#pragma once

#ifndef __APPLE__
#define _Nonnull
#define _Nullable
#endif

// MARK: Rust FFI required types

typedef uint8_t rust_bool_t;
typedef uintptr_t rust_usize_t;

typedef struct rust_slice_s {
    void *_Nullable data;
    uintptr_t len;
} rust_slice_t;

#if _WIN32
typedef wchar_t rust_path_t;
#else
typedef char rust_path_t;
#endif

// MARK: Rust error handling constructs

char *_Nullable pahkat_client_err = NULL;

static void pahkat_client_err_callback(const char *_Nonnull msg) {
    size_t sz = strlen(msg) + 1;
    pahkat_client_err = (char*)calloc(1, sz);
    memcpy(pahkat_client_err, msg, sz);
}

static void pahkat_client_err_print() {
    if (pahkat_client_err != NULL) {
        printf("Err: %s\n", pahkat_client_err);
    }
}

static void pahkat_client_err_free() {
    if (pahkat_client_err != NULL) {
        free(pahkat_client_err);
        pahkat_client_err = NULL;
    }
}

#define ERR_CALLBACK void (*_Nonnull exception)(const char *_Nonnull)

// MARK: Pahkat structs

typedef struct package_status_s {
    rust_bool_t is_system;
    int8_t status;
} package_status_t;

typedef char json_str_t;

// MARK: Prefix functions

extern void *_Nullable
pahkat_prefix_package_store_create(const rust_path_t *_Nonnull path, ERR_CALLBACK);

extern void *_Nullable
pahkat_prefix_package_store_open(const rust_path_t *_Nonnull path, ERR_CALLBACK);

extern package_status_t
pahkat_prefix_package_store_status(void *_Nonnull handle, const char *_Nonnull package_key, ERR_CALLBACK);

extern const rust_path_t *_Nullable
pahkat_prefix_package_store_import(void *_Nonnull handle, const char *_Nonnull package_key, const rust_path_t *_Nonnull installer_path, ERR_CALLBACK);

// Should be using NSURLSession for this
//
//extern const rust_path_t *_Nullable
//pahkat_prefix_package_store_download(
//     const void *_Nonnull handle,
//     const char *_Nonnull package_key,
//     void (*_Nonnull progress)(const void *_Nonnull, uint64_t, uint64_t),
//     ERR_CALLBACK
// );

// pahkat_prefix_package_store_clear_cache
// pahkat_prefix_package_store_refresh_repos
// pahkat_prefix_package_store_force_refresh_repos
// pahkat_prefix_package_store_repo_indexes
// pahkat_prefix_package_store_config

// pahkat_prefix_transaction_new
// pahkat_prefix_transaction_actions
// pahkat_prefix_transaction_process

// pahkat_store_config_set_ui_value
// pahkat_store_config_ui_value
// pahkat_store_config_skipped_package
// pahkat_store_config_repos
// pahkat_store_config_set_repos

// MARK: macOS functions

extern void *_Nonnull
pahkat_macos_package_store_default();

extern void *_Nullable
pahkat_macos_package_store_new(const rust_path_t *_Nonnull path, ERR_CALLBACK);

extern void *_Nullable
pahkat_macos_package_store_load(const rust_path_t *_Nonnull path, ERR_CALLBACK);

extern package_status_t
pahkat_macos_package_store_status(void *_Nonnull handle, const char *_Nonnull package_key, ERR_CALLBACK);
        
extern rust_path_t *_Nullable
pahkat_macos_package_store_download(void *_Nonnull handle,
                                    const char *_Nonnull package_key,
                                    void (*_Nonnull progress)(const void *_Nonnull, uint64_t, uint64_t),
                                    ERR_CALLBACK);

extern void pahkat_macos_package_store_clear_cache(void *_Nonnull handle, ERR_CALLBACK);
extern void pahkat_macos_package_store_refresh_repos(void *_Nonnull handle, ERR_CALLBACK);
extern void pahkat_macos_package_store_force_refresh_repos(void *_Nonnull handle, ERR_CALLBACK);

extern const char *_Nullable
pahkat_macos_package_store_repo_indexes(void *_Nonnull handle, ERR_CALLBACK);
        
extern const void *_Nullable
pahkat_macos_package_store_config(void *_Nonnull handle, ERR_CALLBACK);

// MARK: macOS Transaction functions

extern const void *_Nullable
pahkat_macos_transaction_new(void *_Nonnull handle,
                             const json_str_t *_Nonnull actions,
                             ERR_CALLBACK);
            
extern const json_str_t *_Nullable
pahkat_macos_transaction_actions(void *_Nonnull handle, ERR_CALLBACK);

extern void
pahkat_macos_transaction_process(void *_Nonnull handle,
                                 uint32_t tag,
                                 void (*_Nonnull progress)(uint32_t, const char *_Nonnull, uint32_t),
                                 ERR_CALLBACK);

// MARK: Store config functions

extern void
pahkat_store_config_set_ui_value(void *_Nonnull handle, const char *_Nonnull key, const char *_Nullable value, ERR_CALLBACK);

extern const char *_Nullable
pahkat_store_config_ui_value(void *_Nonnull handle, const char *_Nonnull key, ERR_CALLBACK);

extern const char *_Nullable
pahkat_store_config_skipped_package(void *_Nonnull handle, const char *_Nonnull package_key, ERR_CALLBACK);

extern const json_str_t *_Nullable
pahkat_store_config_repos(void *_Nonnull handle, ERR_CALLBACK);

extern void
pahkat_store_config_set_repos(void *_Nonnull handle, const json_str_t *_Nonnull repos, ERR_CALLBACK);

#ifdef __cplusplus
}
#endif
