#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>

// Function to execute system commands
int executeCommand(const char* command) {
    return system(command);
}

// Function executed when the "Backup" button is clicked
static void on_backup_button_clicked(GtkWidget *widget, gpointer data) {
    // Execute backup command
    int result = executeCommand("dconf dump / > gnome-settings-backup.dconf");
    
    if (result == 0) {
        std::cout << "Settings have been backed up to 'gnome-settings-backup.dconf'" << std::endl;
    } else {
        std::cerr << "Error during backup." << std::endl;
    }
}

// Function executed when the "Reset" button is clicked
static void on_reset_button_clicked(GtkWidget *widget, gpointer data) {
    // Execute reset command
    int result = executeCommand("dconf reset -f /");

    if (result == 0) {
        std::cout << "Settings have been reset." << std::endl;
    } else {
        std::cerr << "Error during reset." << std::endl;
    }
}

// Function executed when the "Restore" button is clicked
static void on_restore_button_clicked(GtkWidget *widget, gpointer data) {
    // Execute restore command
    int result = executeCommand("dconf load / < gnome-settings-backup.dconf");

    if (result == 0) {
        std::cout << "Settings have been restored from the backup file." << std::endl;
    } else {
        std::cerr << "Error during restoration." << std::endl;
    }
}

// Function to show the "About" window
static void show_about_dialog(GtkWidget *widget, gpointer data) {
    GtkWidget *about_dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Description of your program:\nYour Program Name\n\nAuthor:\nYour Name\n\nEmail: frank@simens.dk\n\nWebsite: https://www.112support.dk"
    );

    gtk_window_set_title(GTK_WINDOW(about_dialog), "About the Program");
    gtk_dialog_run(GTK_DIALOG(about_dialog));
    gtk_widget_destroy(about_dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *backup_button;
    GtkWidget *reset_button;
    GtkWidget *restore_button;
    GtkWidget *about_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GNOME Backup and Reset");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    backup_button = gtk_button_new_with_label("Backup Settings");
    reset_button = gtk_button_new_with_label("Reset Settings");
    restore_button = gtk_button_new_with_label("Restore Settings from Backup");
    about_button = gtk_button_new_with_label("About the Program");

    g_signal_connect(backup_button, "clicked", G_CALLBACK(on_backup_button_clicked), NULL);
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_button_clicked), NULL);
    g_signal_connect(restore_button, "clicked", G_CALLBACK(on_restore_button_clicked), NULL);
    g_signal_connect(about_button, "clicked", G_CALLBACK(show_about_dialog), NULL);

    gtk_box_pack_start(GTK_BOX(box), backup_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), reset_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), restore_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), about_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

// Compile info :
// g++ -o resetubuntuuk resetubuntuuk.cpp `pkg-config --cflags --libs gtk+-3.0`

