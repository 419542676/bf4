/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "tree/ParseTree.h"
#include "tree/ParseTreeVisitor.h"

namespace antlr4 {
namespace tree {

  class ANTLR4CPP_PUBLIC AbstractParseTreeVisitor : public ParseTreeVisitor {
  public:
    /// The default implementation calls <seealso cref="ParseTree#accept"/> on the
    /// specified tree.
    ///默认实现调用传入树的accept方法。这是访问者模式中的一个核心方法，用于开始对解析树的访问过程。
    virtual std::any visit(ParseTree *tree) override {
      return tree->accept(this);
    }

    /**
     * <p>The default implementation initializes the aggregate result to
     * {@link #defaultResult defaultResult()}. Before visiting each child, it
     * calls {@link #shouldVisitNextChild shouldVisitNextChild}; if the result
     * is {@code false} no more children are visited and the current aggregate
     * result is returned. After visiting a child, the aggregate result is
     * updated by calling {@link #aggregateResult aggregateResult} with the
     * previous aggregate result and the result of visiting the child.</p>
     *
     * <p>The default implementation is not safe for use in visitors that modify
     * the tree structure. Visitors that modify the tree should override this
     * method to behave properly in respect to the specific algorithm in use.</p>
     */
     ///负责访问解析树中所有子节点的逻辑。它首先初始化聚合结果为 defaultResult() 的返回值，
     /// 然后遍历所有子节点，对每个子节点调用 accept 方法。在访问每个子节点之前，
     /// 它会调用 shouldVisitNextChild 来决定是否继续访问后续的子节点。
     /// 访问完所有子节点后，或者 shouldVisitNextChild 返回 false 时，返回聚合结果。
    virtual std::any visitChildren(ParseTree *node) override {
      std::any result = defaultResult();
      size_t n = node->children.size();
      for (size_t i = 0; i < n; i++) {
          //判断是否继续访问,未重写默认为true
        if (!shouldVisitNextChild(node, result)) {
          break;
        }
        //继续访问子节点
        std::any childResult = node->children[i]->accept(this);
        //aggregateResult 方法的作用是将对解析树中每个子节点的访问结果进行合并，
        // 以便在访问完所有子节点或者决定不再继续访问时，能够提供一个综合的结果。
        result = aggregateResult(std::move(result), std::move(childResult));
      }

      return result;
    }

    /// The default implementation returns the result of
    /// <seealso cref="#defaultResult defaultResult"/>.
    virtual std::any visitTerminal(TerminalNode * /*node*/) override {
      return defaultResult();
    }

    /// The default implementation returns the result of
    /// <seealso cref="#defaultResult defaultResult"/>.
    virtual std::any visitErrorNode(ErrorNode * /*node*/) override {
      return defaultResult();
    }

  protected:
    /// <summary>
    /// Gets the default value returned by visitor methods. This value is
    /// returned by the default implementations of
    /// <seealso cref="#visitTerminal visitTerminal"/>, <seealso cref="#visitErrorNode visitErrorNode"/>.
    /// The default implementation of <seealso cref="#visitChildren visitChildren"/>
    /// initializes its aggregate result to this value.
    /// <p/>
    /// The base implementation returns {@code std::any()}.
    /// </summary>
    /// <returns> The default value returned by visitor methods. </returns>
    ///返回访问者方法的默认值。visitChildren 方法使用这个值来初始化聚合结果，
    /// 而 visitTerminal 和 visitErrorNode 方法则直接返回这个值。
    virtual std::any defaultResult() {
      return std::any();
    }

    /// <summary>
    /// Aggregates the results of visiting multiple children of a node. After
    /// either all children are visited or <seealso cref="#shouldVisitNextChild"/> returns
    /// {@code false}, the aggregate value is returned as the result of
    /// <seealso cref="#visitChildren"/>.
    /// <p/>
    /// The default implementation returns {@code nextResult}, meaning
    /// <seealso cref="#visitChildren"/> will return the result of the last child visited
    /// (or return the initial value if the node has no children).
    /// </summary>
    /// <param name="aggregate"> The previous aggregate value. In the default
    /// implementation, the aggregate value is initialized to
    /// <seealso cref="#defaultResult"/>, which is passed as the {@code aggregate} argument
    /// to this method after the first child node is visited. </param>
    /// <param name="nextResult"> The result of the immediately preceeding call to visit
    /// a child node.
    /// </param>
    /// <returns> The updated aggregate result. </returns>
    ///用于合并访问子节点得到的结果。默认实现简单地返回 nextResult，即最后一个子节点的访问结果。
    virtual std::any aggregateResult(std::any /*aggregate*/, std::any nextResult) {
      return nextResult;
    }

    /// <summary>
    /// This method is called after visiting each child in
    /// <seealso cref="#visitChildren"/>. This method is first called before the first
    /// child is visited; at that point {@code currentResult} will be the initial
    /// value (in the default implementation, the initial value is returned by a
    /// call to <seealso cref="#defaultResult"/>. This method is not called after the last
    /// child is visited.
    /// <p/>
    /// The default implementation always returns {@code true}, indicating that
    /// {@code visitChildren} should only return after all children are visited.
    /// One reason to override this method is to provide a "short circuit"
    /// evaluation option for situations where the result of visiting a single
    /// child has the potential to determine the result of the visit operation as
    /// a whole.
    /// </summary>
    /// <param name="node"> The <seealso cref="ParseTree"/> whose children are currently being
    /// visited. </param>
    /// <param name="currentResult"> The current aggregate result of the children visited
    /// to the current point.
    /// </param>
    /// <returns> {@code true} to continue visiting children. Otherwise return
    /// {@code false} to stop visiting children and immediately return the
    /// current aggregate result from <seealso cref="#visitChildren"/>. </returns>
    ///在每次访问子节点后被调用，用于决定是否继续访问下一个子节点。默认实现总是返回true，表示继续访问。
    /// 这个方法可以被重写以实现短路逻辑，例如，如果某个子节点的访问结果已经足够决定整个访问操作的结果，
    /// 可以返回false来停止后续的访问。
    virtual bool shouldVisitNextChild(ParseTree * /*node*/, const std::any &/*currentResult*/) {
      return true;
    }

  };

} // namespace tree
} // namespace antlr4
