#include <iostream>
#include <string>

using namespace std;

// ───────────────────────────────────────────────────────────
// 1. Base class defining the template method
// ───────────────────────────────────────────────────────────
class ModelTrainer {
public:
    // The template method — final so subclasses can’t change the sequence
    void trainPipeline(const string& dataPath) {
        loadData(dataPath);
        preprocessData();
        trainModel();      // subclass-specific
        evaluateModel();   // subclass-specific
        saveModel();       // subclass-specific or default
    }
    
    protected:
    void loadData(const string& path) {
        cout << "[Common] Loading dataset from " << path << "\n";
        // e.g., read CSV, images, etc.
    }

    virtual void preprocessData() {
        cout << "[Common] Splitting into train/test and normalizing\n";
    }

    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;

    // Provide a default save, but subclasses can override if needed
    virtual void saveModel() {
        cout << "[Common] Saving model to disk as default format\n";
    }
};