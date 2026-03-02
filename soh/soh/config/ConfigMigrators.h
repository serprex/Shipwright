namespace SOH {
enum class MigrationAction {
    Rename,
    Remove,
};

struct Migration {
    const char* from;
    const char* to;
};
} // namespace SOH
