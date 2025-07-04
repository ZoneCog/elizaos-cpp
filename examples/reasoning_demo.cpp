#include "elizaos/core.hpp"
#include <iostream>
#include <memory>

using namespace elizaos;

// Simple demonstration of the reasoning engine capabilities
int main() {
    std::cout << "ElizaOS C++ Reasoning Engine Demo" << std::endl;
    std::cout << "==================================" << std::endl;
    
    // 1. Demonstrate TruthValue operations
    std::cout << "\n1. Truth Value Operations (PLN-style)" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    
    TruthValue tv1(0.8, 0.9);  // High strength, high confidence
    TruthValue tv2(0.6, 0.7);  // Medium strength, good confidence
    
    std::cout << "TV1: strength=" << tv1.strength << ", confidence=" << tv1.confidence << std::endl;
    std::cout << "TV2: strength=" << tv2.strength << ", confidence=" << tv2.confidence << std::endl;
    
    auto conjunction = tv1.conjunction(tv2);
    auto disjunction = tv1.disjunction(tv2);
    auto implication = tv1.implication(tv2);
    auto negation = tv1.negation();
    
    std::cout << "Conjunction: " << conjunction.strength << ", " << conjunction.confidence << std::endl;
    std::cout << "Disjunction: " << disjunction.strength << ", " << disjunction.confidence << std::endl;
    std::cout << "Implication: " << implication.strength << ", " << implication.confidence << std::endl;
    std::cout << "Negation of TV1: " << negation.strength << ", " << negation.confidence << std::endl;
    
    // 2. Demonstrate PLN Inference Engine
    std::cout << "\n2. PLN Inference Engine" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    PLNInferenceEngine plnEngine;
    
    // Add some inference rules
    InferenceRule rule1("human_mortal", "human(?X)", "mortal(?X)", TruthValue(0.95, 0.99));
    InferenceRule rule2("socrates_human", "Socrates", "human(Socrates)", TruthValue(1.0, 1.0));
    
    plnEngine.addRule(rule1);
    plnEngine.addRule(rule2);
    
    std::cout << "Added rules:" << std::endl;
    std::cout << "  - " << rule1.name << ": " << rule1.pattern << " -> " << rule1.conclusion << std::endl;
    std::cout << "  - " << rule2.name << ": " << rule2.pattern << " -> " << rule2.conclusion << std::endl;
    
    // Create a test state
    AgentConfig config{"demo-agent", "Demo Agent", "Reasoning demonstration agent", "Educational example", "logical"};
    State state(config);
    
    // Test forward chaining
    auto forwardResults = plnEngine.forwardChain(state, "Socrates", 3);
    std::cout << "\nForward chaining results for 'Socrates':" << std::endl;
    for (const auto& result : forwardResults) {
        std::cout << "  Conclusion: " << result.conclusion 
                  << " (confidence: " << result.confidence << ")" << std::endl;
        for (const auto& step : result.reasoningChain) {
            std::cout << "    - " << step << std::endl;
        }
    }
    
    // Test best inference
    auto bestResult = plnEngine.bestInference(state, "human(Socrates)");
    std::cout << "\nBest inference for 'human(Socrates)':" << std::endl;
    std::cout << "  Result: " << bestResult.conclusion 
              << " (confidence: " << bestResult.confidence << ")" << std::endl;
    
    // 3. Demonstrate Cognitive Fusion Engine with uncertainty
    std::cout << "\n3. Cognitive Fusion Engine with Uncertainty" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    
    CognitiveFusionEngine fusionEngine;
    
    // Get the PLN engine from the fusion engine and add rules to it
    auto plnEnginePtr = fusionEngine.getPLNEngine();
    plnEnginePtr->addRule(rule1);
    plnEnginePtr->addRule(rule2);
    
    // Create and integrate some memories
    auto memory1 = std::make_shared<Memory>("mem-1", "Socrates is a human philosopher", "socrates", config.agentId);
    auto memory2 = std::make_shared<Memory>("mem-2", "All humans are mortal beings", "knowledge", config.agentId);
    
    // Add embeddings to simulate semantic similarity
    EmbeddingVector embedding1{0.8f, 0.2f, 0.6f, 0.4f};
    EmbeddingVector embedding2{0.7f, 0.3f, 0.5f, 0.5f};
    memory1->setEmbedding(embedding1);
    memory2->setEmbedding(embedding2);
    
    fusionEngine.integrateMemory(memory1);
    fusionEngine.integrateMemory(memory2);
    
    // Build AtomSpace from memories
    fusionEngine.buildAtomSpaceFromMemories();
    
    auto nodes = fusionEngine.getAtomSpaceNodes();
    auto edges = fusionEngine.getAtomSpaceEdges();
    
    std::cout << "Built AtomSpace with " << nodes.size() << " nodes and " << edges.size() << " edges" << std::endl;
    
    // Process a query with uncertainty
    auto result = fusionEngine.processQueryWithUncertainty(state, "mortal");
    
    std::cout << "\nUncertainty-aware reasoning results for 'mortal':" << std::endl;
    std::cout << "  Symbolic results: " << result.symbolicResults.size() << std::endl;
    std::cout << "  Connectionist results: " << result.connectionistResults.size() << std::endl;
    std::cout << "  PLN results: " << result.plnResults.size() << std::endl;
    std::cout << "  Fused results: " << result.fusedResults.size() << std::endl;
    std::cout << "  Overall confidence: " << result.confidence << std::endl;
    std::cout << "  Overall truth: strength=" << result.overallTruth.strength 
              << ", confidence=" << result.overallTruth.confidence << std::endl;
    
    // 4. Demonstrate Memory retrieval
    std::cout << "\n4. Memory Retrieval" << std::endl;
    std::cout << "-------------------" << std::endl;
    
    auto relevantMemories = fusionEngine.retrieveRelevantMemories("human", 5);
    std::cout << "Found " << relevantMemories.size() << " relevant memories for 'human':" << std::endl;
    for (const auto& memory : relevantMemories) {
        std::cout << "  - " << memory->getId() << ": " << memory->getContent() << std::endl;
    }
    
    std::cout << "\nDemo completed successfully!" << std::endl;
    return 0;
}